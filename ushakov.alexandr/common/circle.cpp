#include "circle.hpp"

#include <cmath>
#include <iostream>

ushakov::Circle::Circle(const point_t& position, double radius) :
  position_(position),
  radius_(radius)
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Circle constructor error: Invalid radius(" + std::to_string(radius) + ')');
  }
}

void ushakov::Circle::move(const point_t& newPosition) noexcept
{
  position_ = newPosition;
}

void ushakov::Circle::move(double xAxis, double yAxis) noexcept
{
  position_.x += xAxis;
  position_.y += yAxis;
}

void ushakov::Circle::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Circle scale error: Invalid coefficient of scale, it must be positive("
          + std::to_string(coefficient) + ')');
  }

  radius_ *= coefficient;
}

double ushakov::Circle::getRadius() const noexcept
{
  return radius_;
}

double ushakov::Circle::getArea() const noexcept
{
  return M_PI * radius_ * radius_;
}

ushakov::rectangle_t ushakov::Circle::getFrameRect() const noexcept
{
  return rectangle_t{2 * radius_, 2 * radius_, position_};
}

ushakov::point_t ushakov::Circle::getPosition() const noexcept
{
  return position_;
}

void ushakov::Circle::print() const noexcept
{
  std::cout << "Circle" << std::endl;

  std::cout << "  radius = " << radius_ << std::endl;
  std::cout << "  center: x = " << position_.x << ", y = " << position_.y << std::endl;
  std::cout << "  area: " << getArea() << std::endl;
}

void ushakov::Circle::printFrameRectangle() const noexcept
{
  rectangle_t rectangle = getFrameRect();

  std::cout << "Frame rectangle for this shape:" << std::endl;
  std::cout << "  height = " << rectangle.height << ",  width = " << rectangle.width << std::endl;
  std::cout << "  position: x = " << rectangle.pos.x << ", y = " << rectangle.pos.y << std::endl;
}
