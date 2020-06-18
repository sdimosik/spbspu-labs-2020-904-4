#include "circle.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

namespace stolyarov
{
  Circle::Circle(double radius, const point_t& pos) :
    Shape(pos),
    radius_(radius)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("Incorrect argument radius was given: " + std::to_string(radius));
    }
  }

  void Circle::move(double x, double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Circle::move(const point_t& pos) noexcept
  {
    pos_ = pos;
  }

  double Circle::getArea() const noexcept
  {
    return (M_PI * radius_ * radius_);
  }

  rectangle_t Circle::getFrameRect() const noexcept
  {
    return rectangle_t({ 2 * radius_,2 * radius_,pos_ });
  }

  point_t Circle::getCenter() const noexcept
  {
    return pos_;
  }

  void Circle::printInf()
  {
    std::cout << "Circle information" << '\n'
        << "Center's location:" << '\n'
        << "x: " << pos_.x << '\n' << "y: " << pos_.y << '\n'
        << "Parameters of the circle:" << '\n'
        << "radius: " << radius_ << '\n'
        << "Area of the circle: " << getArea() << '\n' << '\n';
  }

  void Circle::printFrameInf()
  {
    std::cout << "Frame information" << '\n'
        << "Center's location:" << '\n'
        << "x: " << getFrameRect().pos.x << '\n' << "y: " << getFrameRect().pos.y << '\n'
        << "Parameters of the frame:" << '\n'
        << "height: " << getFrameRect().height << '\n' << "widht: " << getFrameRect().width << '\n' << '\n';
  }

  void Circle::scale(const double rate)
  {
    if (rate <= 0)
    {
      throw std::invalid_argument("Incorrect argument rate was given: " + std::to_string(rate));
    }
    radius_ *= rate;
  }

  void Circle::rotate(const double) noexcept
  {}
}
