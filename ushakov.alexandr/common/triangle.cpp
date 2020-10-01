#include "triangle.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

#include "detail.hpp"

const int FULL_CIRCLE = 180;

ushakov::Triangle::Triangle(const point_t& top1, const point_t& top2, const point_t& top3) :
  tops_{top1, top2, top3}
{
  double a = ushakov::detail::getDistance(tops_[0], tops_[1]);
  double b = ushakov::detail::getDistance(tops_[1], tops_[2]);
  double c = ushakov::detail::getDistance(tops_[2], tops_[0]);

  if (a + b <= c || a + c <= b || b + c <= a)
  {
    throw std::invalid_argument("Triangle constructor error: Invalid triangle vertexes. It is not a triangle");
  }
}

void ushakov::Triangle::move(const point_t& newPosition) noexcept
{
  const point_t position = getPosition();

  const double xAxis = newPosition.x - position.x;
  const double yAxis = newPosition.y - position.y;

  move(xAxis, yAxis);
}

void ushakov::Triangle::move(double xAxis, double yAxis) noexcept
{
  for (point_t& top : tops_)
  {
    top.x += xAxis;
    top.y += yAxis;
  }
}

void ushakov::Triangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Triangle scale error: Invalid coefficient of scale, it must be positive("
          + std::to_string(coefficient) + ')');
  }

  const point_t position = getPosition();

  tops_[0].x = position.x + (position.x - tops_[0].x) * coefficient;
  tops_[0].y = position.y + (position.y - tops_[0].y) * coefficient;

  tops_[1].x = position.x + (position.x - tops_[1].x) * coefficient;
  tops_[1].y = position.y + (position.y - tops_[1].y) * coefficient;

  tops_[2].x = position.x + (position.x - tops_[2].x) * coefficient;
  tops_[2].y = position.y + (position.y - tops_[2].y) * coefficient;
}

void ushakov::Triangle::rotate(double angle) noexcept
{
  const double angleInRadians = angle * M_PI / FULL_CIRCLE;
  const double sinValue = std::sin(angleInRadians);
  const double cosValue = std::cos(angleInRadians);
  const point_t position = getPosition();

  for (point_t& top : tops_)
  {
    const double previousX = top.x;

    top.x = position.x + (top.x - position.x) * cosValue - (top.y - position.y) * sinValue;
    top.y = position.y + (top.y - position.y) * cosValue + (previousX - position.x) * sinValue;
  }
}

double ushakov::Triangle::getArea() const noexcept
{
  // Heron's formula is used

  double a = ushakov::detail::getDistance(tops_[0], tops_[1]);
  double b = ushakov::detail::getDistance(tops_[1], tops_[2]);
  double c = ushakov::detail::getDistance(tops_[2], tops_[0]);
  double p = (a + b + c) / 2;

  return sqrt(p * (p - a) * (p - b) * (p - c));
}

ushakov::rectangle_t ushakov::Triangle::getFrameRect() const noexcept
{
  double xMin = std::min({tops_[0].x, tops_[1].x, tops_[2].x});
  double xMax = std::max({tops_[0].x, tops_[1].x, tops_[2].x});
  double yMin = std::min({tops_[0].y, tops_[1].y, tops_[2].y});
  double yMax = std::max({tops_[0].y, tops_[1].y, tops_[2].y});

  return rectangle_t{xMax - xMin, yMax - yMin, point_t{xMin + (xMax - xMin) / 2, yMin + (yMax - yMin) / 2}};
}

ushakov::point_t ushakov::Triangle::getPosition() const noexcept
{
  return point_t{(tops_[0].x + tops_[1].x + tops_[2].x) / 3, (tops_[0].y + tops_[1].y + tops_[2].y) / 3};
}

void ushakov::Triangle::print() const noexcept
{
  std::cout << "Triangle" << std::endl;

  std::cout << "  vertexes:" << std::endl;

  std::cout << "    1: x = " << tops_[0].x << ", y = " << tops_[0].y << std::endl;
  std::cout << "    2: x = " << tops_[1].x << ", y = " << tops_[1].y << std::endl;
  std::cout << "    3: x = " << tops_[2].x << ", y = " << tops_[2].y << std::endl;

  std::cout << "  area: " << getArea() << std::endl;
}

void ushakov::Triangle::printFrameRectangle() const noexcept
{
  const rectangle_t rectangle = getFrameRect();

  std::cout << "Frame rectangle for this shape:" << std::endl;
  std::cout << "  height = " << rectangle.height << ",  width = " << rectangle.width << std::endl;
  std::cout << "  position: x = " << rectangle.pos.x << ", y = " << rectangle.pos.y << std::endl;
}
