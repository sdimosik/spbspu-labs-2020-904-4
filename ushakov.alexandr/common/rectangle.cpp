#include "rectangle.hpp"

#include <algorithm>
#include <cmath>
#include <iostream>

#include "detail.hpp"

const int FULL_CIRCLE = 180;

ushakov::Rectangle::Rectangle(double width, double height, const point_t& position) :
  tops_{{position.x - width / 2, position.y + height / 2},
        {position.x + width / 2, position.y + height / 2},
        {position.x + width / 2, position.y - height / 2},
        {position.x - width / 2, position.y - height / 2}}
{
  if (width <= 0)
  {
    if (height <= 0)
    {
      throw std::invalid_argument("Rectangle constructor error: Invalid width and height of rectangle("
            + std::to_string(width) + " and " + std::to_string(height) + ')');
    }

    throw std::invalid_argument("Rectangle constructor error: Invalid width of rectangle, it must be positive("
          + std::to_string(width) + ')');
  }

  if (height <= 0)
  {
    throw std::invalid_argument("Rectangle constructor error: Invalid height of rectangle, it must be positive"
          + std::to_string(height) + ')');
  }
}

void ushakov::Rectangle::move(const point_t& newPosition) noexcept
{
  move(newPosition.x - getPosition().x, newPosition.y - getPosition().y);
}

void ushakov::Rectangle::move(double xAxis, double yAxis) noexcept
{
  for (point_t& top : tops_)
  {
    top.x += xAxis;
    top.y += yAxis;
  }
}

void ushakov::Rectangle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Rectangle scale error: Invalid coefficient of scale, it must be positive("
          + std::to_string(coefficient) + ')');
  }

  const point_t position = getPosition();

  for (point_t& top : tops_)
  {
    top.x = position.x + (top.x - position.x) * coefficient;
    top.y = position.y + (top.y - position.y) * coefficient;
  }
}

void ushakov::Rectangle::rotate(double angle) noexcept
{
  const double angleInRadians = angle * M_PI / FULL_CIRCLE;
  const double sinValue = std::sin(angleInRadians);
  const double cosValue = std::cos(angleInRadians);
  const point_t position = getPosition();

  for (point_t& top : tops_)
  {
    const double previousX = top.x;

    top.x = position.x + (top.x - position.x) * cosValue - (top.y - position.y) * sinValue;
    top.y = position.y + (previousX - position.x) * sinValue + (top.y - position.y) * cosValue;
  }
}

double ushakov::Rectangle::getWidth() const noexcept
{
  return ushakov::detail::getDistance(tops_[0], tops_[1]);
}

double ushakov::Rectangle::getHeight() const noexcept
{
  return ushakov::detail::getDistance(tops_[0], tops_[3]);
}

double ushakov::Rectangle::getArea() const noexcept
{
  return getWidth() * getHeight();
}

ushakov::rectangle_t ushakov::Rectangle::getFrameRect() const noexcept
{
  double xMax = std::max({tops_[0].x, tops_[1].x, tops_[2].x, tops_[3].x});
  double xMin = std::min({tops_[0].x, tops_[1].x, tops_[2].x, tops_[3].x});
  double yMax = std::max({tops_[0].y, tops_[1].y, tops_[2].y, tops_[3].y});
  double yMin = std::min({tops_[0].y, tops_[1].y, tops_[2].y, tops_[3].y});

  return rectangle_t{xMax - xMin, yMax - yMin, {(xMax + xMin) / 2, (yMax + yMin) / 2}};
}

ushakov::point_t ushakov::Rectangle::getPosition() const noexcept
{
  return point_t{(tops_[0].x + tops_[2].x) / 2, (tops_[0].y + tops_[2].y) / 2};
}

void ushakov::Rectangle::print() const noexcept
{
  std::cout << "Rectangle" << std::endl;
  std::cout << "  corners:" << std::endl;

  for (int i = 0; i < 4; i++)
  {
    std::cout << "    " << i + 1 << ": x = " << tops_[i].x << ", y = " << tops_[i].y << std::endl;
  }

  std::cout << "  height = " << getHeight() << ", width = " << getWidth() << std::endl;
  std::cout << "  position: x = " << getPosition().x << ", y = " << getPosition().y << std::endl;
  std::cout << "  area: " << getArea() << std::endl;
}

void ushakov::Rectangle::printFrameRectangle() const noexcept
{
  const rectangle_t rectangle = getFrameRect();

  std::cout << "Frame rectangle for this shape:" << std::endl;
  std::cout << "  height = " << rectangle.height << ",  width = " << rectangle.width << std::endl;
  std::cout << "  position: x = " << rectangle.pos.x << ", y = " << rectangle.pos.y << std::endl;
}
