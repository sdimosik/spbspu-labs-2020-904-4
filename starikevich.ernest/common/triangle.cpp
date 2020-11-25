#include "triangle.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

namespace starikevich
{
  Triangle::Triangle(const point_t& peak1, const point_t& peak2, const point_t& peak3) :
    peaks_{ peak1, peak2, peak3 }
  {
    double side1 = std::sqrt((peaks_[0].x - peaks_[1].x) * (peaks_[0].x - peaks_[1].x) + (peaks_[0].y - peaks_[1].y) * (peaks_[0].y - peaks_[1].y)),
      side2 = std::sqrt((peaks_[1].x - peaks_[2].x) * (peaks_[1].x - peaks_[2].x) + (peaks_[1].y - peaks_[2].y) * (peaks_[1].y - peaks_[2].y)),
      side3 = std::sqrt((peaks_[2].x - peaks_[0].x) * (peaks_[2].x - peaks_[0].x) + (peaks_[2].y - peaks_[0].y) * (peaks_[2].y - peaks_[0].y));
    if (side1 + side2 <= side3 || side1 + side3 <= side2 || side3 + side2 <= side1)
    {
      throw std::invalid_argument("The sum of the two sides of the triangle must be greater than the third side. Sizes of the sides = "
        + std::to_string(side1) + "; " + std::to_string(side2) + "; " + std::to_string(side3) + ". Largest side = " + std::to_string(std::max(std::max(side1, side2), side3)));
    }
  }

  void Triangle::move(const point_t& pos) noexcept
  {
    move(pos.x - getPosition().x, pos.y - getPosition().y);
  }

  void Triangle::move(double x, double y) noexcept
  {
    for (size_t i = 0; i < 3; i++)
    {
      peaks_[i].x += x;
      peaks_[i].y += y;
    }
  }

  rectangle_t Triangle::getFrameRect() const noexcept
  {
    double maxX = std::max({ peaks_[0].x, peaks_[1].x, peaks_[2].x}),
      minX = std::min({ peaks_[0].x, peaks_[1].x, peaks_[2].x}),
      maxY = std::max({ peaks_[0].y, peaks_[1].y, peaks_[2].y}),
      minY = std::min({ peaks_[0].y, peaks_[1].y, peaks_[2].y});
    return { maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2} };
  }

  double Triangle::getSide1() const noexcept
  {
    return std::sqrt((peaks_[1].x - peaks_[0].x) * (peaks_[1].x - peaks_[0].x) + (peaks_[1].y - peaks_[0].y) * (peaks_[1].y - peaks_[0].y));
  }

  double Triangle::getSide2() const noexcept
  {
    return std::sqrt((peaks_[1].x - peaks_[2].x) * (peaks_[1].x - peaks_[2].x) + (peaks_[1].y - peaks_[2].y) * (peaks_[1].y - peaks_[2].y));
  }

  double Triangle::getSide3() const noexcept
  {
    return std::sqrt((peaks_[2].x - peaks_[0].x) * (peaks_[2].x - peaks_[0].x) + (peaks_[2].y - peaks_[0].y) * (peaks_[2].y - peaks_[0].y));
  }

  point_t Triangle::getPosition() const noexcept
  {
    return {(peaks_[0].x + peaks_[1].x + peaks_[2].x) / 3, (peaks_[0].y + peaks_[1].y + peaks_[2].y) / 3};
  }

  double Triangle::getArea() const noexcept
  {
    double p = (getSide1() + getSide2() + getSide3()) / 2;
    double area = std::sqrt(p * (p - getSide1()) * (p - getSide2()) * (p - getSide3()));
    return area;
  }

  void Triangle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficient of scale must be positive number. Coefficient = " + std::to_string(coefficient));
    }
    const point_t center = getPosition();
    for (size_t i = 0; i < 3; i++)
    {
      peaks_[i].x = center.x + (peaks_[i].x - center.x) * coefficient;
      peaks_[i].y = center.y + (peaks_[i].y - center.y) * coefficient;
    }
  }

  void Triangle::rotate(double angle) noexcept
  {
    double angle_radian = (angle * M_PI) / 180;
    const double sin = std::sin(angle_radian), cos = std::cos(angle_radian);
    const point_t center = getPosition();
    for (size_t i = 0; i < 3; i++)
    {
      const double oldX = peaks_[i].x;
      peaks_[i].x = center.x + (oldX - center.x) * cos - (peaks_[i].y - center.y) * sin;
      peaks_[i].y = center.y + (oldX - center.x) * sin + (peaks_[i].y - center.y) * cos;
    }
  }
}
