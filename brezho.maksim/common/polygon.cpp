#include "polygon.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>  

namespace brezho
{
  Polygon::Polygon(const point_t array[], size_t size):
    peaks_(std::make_unique<point_t[]>(size)),
    size_(size)
  {
    if (size < 3)
    {
      throw std::out_of_range("The size of the array of points is too small, it must be greater than 2. Size = " + std::to_string(size));
    }
    double xVectorA = array[1].x - array[0].x,
      yVectorA = array[1].y - array[0].y,
      xVectorB = array[2].x - array[1].x,
      yVectorB = array[2].y - array[1].y,
      det = xVectorA * yVectorB - yVectorA * xVectorB;
    if (det == 0)
    {
      throw std::invalid_argument("A point cannot be on the same straight line as two neighboring points. Point number = " + std::to_string(1));
    }
    bool isNegativeDet = (det < 0);
    peaks_[0] = array[0];
    for (size_t i = 1; i < size; i++)
    {
      double xVectorA = array[(i + 1) % size].x - array[i].x,
        yVectorA = array[(i + 1) % size].y - array[i].y,
        xVectorB = array[(i + 2) % size].x - array[(i + 1) % size].x,
        yVectorB = array[(i + 2) % size].y - array[(i + 1) % size].y,
        det1 = xVectorA * yVectorB - yVectorA * xVectorB;
      if (det1 == 0)
      {
        throw std::invalid_argument("A point cannot be on the same straight line as two neighboring points. Point number = " + std::to_string((i + 1) % size));
      }
      bool isNegativeDet1 = (det1 < 0);
      if (isNegativeDet != isNegativeDet1)
      {
        throw std::invalid_argument("The polygon must be convex");
      }
      peaks_[i] = array[i];
    }
  }

  Polygon::Polygon(const Polygon& otherPolygon) :
    peaks_(std::make_unique<point_t[]>(otherPolygon.size_)),
    size_(otherPolygon.size_)
  {
    for (size_t i = 0; i < otherPolygon.size_; i++)
    {
      peaks_[i] = otherPolygon.peaks_[i];
    }
  }

  Polygon::Polygon(Polygon&& otherPolygon) noexcept :
    peaks_(std::move(otherPolygon.peaks_)),
    size_(otherPolygon.size_)
  {
    otherPolygon.size_ = 0;
  }

  Polygon& Polygon::operator=(const Polygon& otherPolygon)
  {
    if (&otherPolygon == this)
    {
      return *this;
    }
    arrayPtr temp = std::make_unique<point_t[]>(otherPolygon.size_);
    for (size_t i = 0; i < otherPolygon.size_; i++)
    {
      temp[i] = otherPolygon.peaks_[i];
    }
    size_ = otherPolygon.size_;
    peaks_ = std::move(temp);
    return *this;
  }

  Polygon& Polygon::operator=(Polygon&& otherPolygon) noexcept
  {
    if (&otherPolygon == this)
    {
      return *this;
    }
    size_ = otherPolygon.size_;
    peaks_ = std::move(otherPolygon.peaks_);
    otherPolygon.size_ = 0;
    return *this;
  }

  void Polygon::move(const point_t& pos) noexcept
  {
    move(pos.x - getPosition().x, pos.y - getPosition().y);
  }

  void Polygon::move(const double x, const double y) noexcept
  {
    for (size_t i = 0; i < size_; i++)
    {
      peaks_[i].x += x;
      peaks_[i].y += y;
    }
  }

  rectangle_t Polygon::getFrameRect() const noexcept
  {
    double maxX = peaks_[0].x,
      minX = peaks_[0].x,
      maxY = peaks_[0].y,
      minY = peaks_[0].y;
    for (size_t i = 1; i < size_; i++)
    {
      maxX = std::max({ maxX, peaks_[i].x });
      minX = std::min({ minX, peaks_[i].x });
      maxY = std::max({ maxY, peaks_[i].y });
      minY = std::min({ minY, peaks_[i].y });
    }
    return { maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2} };
  }

  size_t Polygon::getPeaksCount() const noexcept
  {
    return size_;
  }

  point_t Polygon::getPeakCoordinates(size_t index)
  {
    if (index > size_ - 1)
    {
      throw std::out_of_range("The index of CompositeShape is outside of acceptable values. Index = " + std::to_string(index));
    }
    return peaks_[index];
  }

  double Polygon::getSide(size_t index)
  {
    if (index > size_ - 1)
    {
      throw std::out_of_range("The index of CompositeShape is outside of acceptable values. Index = " + std::to_string(index));
    }
    return std::sqrt((peaks_[index].x - peaks_[(index + 1) % size_].x) * (peaks_[index].x - peaks_[(index + 1) % size_].x) + (peaks_[index].y - peaks_[(index + 1) % size_].y) * (peaks_[index].y - peaks_[(index + 1) % size_].y));
  }

  point_t Polygon::getPosition() const noexcept
  {
    double posX = 0, posY = 0;
    for (size_t i = 0; i < size_; i++)
    {
      posX += peaks_[i].x;
      posY += peaks_[i].y;
    }
    return { posX / size_, posY / size_};
  }

  double Polygon::getArea() const noexcept
  {
    double sum1 = peaks_[size_ - 1].x * peaks_[0].y,
      sum2 = peaks_[0].x * peaks_[size_ - 1].y;
    for (size_t i = 0; i < size_ - 1; i++)
    {
      sum1 += peaks_[i].x * peaks_[i + 1].y;
      sum2 += peaks_[i + 1].x * peaks_[i].y;
    }
    return 0.5 * std::abs(sum1 - sum2);
  }

  void Polygon::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient of scale must be positive number. Coefficient = " + std::to_string(coefficient));
    }
    const point_t center = getPosition();
    for (size_t i = 0; i < size_; i++)
    {
      peaks_[i].x = center.x + (peaks_[i].x - center.x) * coefficient;
      peaks_[i].y = center.y + (peaks_[i].y - center.y) * coefficient;
    }
  }

  void Polygon::rotate(double angle) noexcept
  {
    double angle_radian = (angle * M_PI) / 180;
    const double sin = std::sin(angle_radian), cos = std::cos(angle_radian);
    const point_t center = getPosition();
    for (size_t i = 0; i < size_; i++)
    {
      const double oldX = peaks_[i].x;
      peaks_[i].x = center.x + (oldX - center.x) * cos - (peaks_[i].y - center.y) * sin;
      peaks_[i].y = center.y + (oldX - center.x) * sin + (peaks_[i].y - center.y) * cos;
    }
  }

}
