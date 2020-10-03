#include "rectangle.hpp"
#include <stdexcept>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

namespace brezho
{
  Rectangle::Rectangle(const point_t& pos, double width, double height) :
    peaks_{ {pos.x - width / 2, pos.y - height / 2},
    {pos.x - width / 2, pos.y + height / 2},
    {pos.x + width / 2, pos.y + height / 2},
    {pos.x + width / 2, pos.y - height / 2}}
  {
    if (width <= 0)
    {
      throw std::invalid_argument("The width of the rectangle must be a positive number. Width = " + std::to_string(width));
    }
    if (height <= 0)
    {
      throw std::invalid_argument("The height of the rectangle must be a positive number. Height = " + std::to_string(height));
    }
  }

  void Rectangle::move(const point_t& pos) noexcept
  {
    move(pos.x - getPosition().x, pos.y - getPosition().y);
  }

  void Rectangle::move(double x, double y) noexcept
  {
    for (size_t i = 0; i < 4; i++)
    {
      peaks_[i].x += x;
      peaks_[i].y += y;
    }
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    double maxX = std::max({ peaks_[0].x, peaks_[1].x, peaks_[2].x, peaks_[3].x }),
      minX = std::min({ peaks_[0].x, peaks_[1].x, peaks_[2].x, peaks_[3].x }),
      maxY = std::max({ peaks_[0].y, peaks_[1].y, peaks_[2].y, peaks_[3].y }),
      minY = std::min({ peaks_[0].y, peaks_[1].y, peaks_[2].y, peaks_[3].y });
    return { maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2} };
  }

  double Rectangle::getWidth() const noexcept
  {
    return std::sqrt((peaks_[3].x - peaks_[0].x) * (peaks_[3].x - peaks_[0].x) + (peaks_[3].y - peaks_[0].y) * (peaks_[3].y - peaks_[0].y));
  }

  double Rectangle::getHeight() const noexcept
  {
    return std::sqrt((peaks_[1].x - peaks_[0].x) * (peaks_[1].x - peaks_[0].x) + (peaks_[1].y - peaks_[0].y) * (peaks_[1].y - peaks_[0].y));
  }

  point_t Rectangle::getPosition() const noexcept
  {
    return {(peaks_[2].x + peaks_[0].x) / 2, (peaks_[2].y + peaks_[0].y) / 2};
  }

  double Rectangle::getArea() const noexcept
  {
    return getWidth() * getHeight();
  }

  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient of scale must be positive number. Coefficient = " + std::to_string(coefficient));
    }
    const point_t center = getPosition();
    for (size_t i = 0; i < 4; i++)
    {
      peaks_[i].x = center.x + (peaks_[i].x - center.x) * coefficient;
      peaks_[i].y = center.y + (peaks_[i].y - center.y) * coefficient;
    }
  }

  void Rectangle::rotate(double angle) noexcept
  {
    double angle_radian = (angle * M_PI) / 180;
    const double sin = std::sin(angle_radian), cos = std::cos(angle_radian);
    const point_t center = getPosition();
    for (size_t i = 0; i < 4; i++)
    {
      const double oldX = peaks_[i].x;
      peaks_[i].x = center.x + (oldX - center.x) * cos - (peaks_[i].y - center.y) * sin;
      peaks_[i].y = center.y + (oldX - center.x) * sin + (peaks_[i].y - center.y) * cos;
    }
  }
}
