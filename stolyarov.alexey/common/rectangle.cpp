#include "rectangle.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

namespace stolyarov
{

  const double CIRCLE_ANGLE = 360.0;

  Rectangle::Rectangle(double width, double height, const point_t& pos) :
    Shape(pos),
    width_(width),
    height_(height),
    angle_(0)
  {
    if (width <= 0)
    {
      throw std::invalid_argument("Incorrect argument width was given: " + std::to_string(width));
    }
    if (height <= 0)
    {
      throw std::invalid_argument("Incorrect argument height was given: " + std::to_string(height));
    }
  }

  void Rectangle::move(double x, double y) noexcept
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Rectangle::move(const point_t& pos) noexcept
  {
    pos_ = pos;
  }

  double Rectangle::getArea() const noexcept
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    double RadAngle = angle_ * M_PI / (CIRCLE_ANGLE / 2);
    return { height_ * fabs(sin(RadAngle)) + width_ * fabs(cos(RadAngle)), width_ * fabs(sin(RadAngle)) + height_ * fabs(cos(RadAngle)), pos_ };
  }

  point_t Rectangle::getCenter() const noexcept
  {
    return pos_;
  }

  void Rectangle::printInf()
  {
    std::cout << "Rectangle information" << '\n'
        << "Center's location:" << '\n'
        << "x: " << pos_.x << '\n' << "y: " << pos_.y << '\n'
        << "Parameters of the rectangle:" << '\n'
        << "height: " << height_ << '\n' << "widht: " << width_ << '\n'
        << "Area of the rectangle: " << getArea() << '\n' << '\n';
  }

  void Rectangle::printFrameInf()
  {
    std::cout << "Frame information" << '\n'
        << "Center's location:" << '\n'
        << "x: " << getFrameRect().pos.x << '\n' << "y: " << getFrameRect().pos.y << '\n'
        << "Parameters of the frame:" << '\n'
        << "height: " << getFrameRect().height << '\n' << "widht: " << getFrameRect().width << '\n' << '\n';
  }

  void Rectangle::scale(const double rate)
  {
    if (rate <= 0)
    {
      throw std::invalid_argument("Incorrect argument rate was given: " + std::to_string(rate));
    }
    height_ *= rate;
    width_ *= rate;
  }

  void Rectangle::rotate(const double angle) noexcept
  {
    angle_ += angle;
    if (angle_ > 0.0)
    {
      angle_ = fmod(angle_, CIRCLE_ANGLE);
    }
    else
    {
      angle_ = CIRCLE_ANGLE + fmod(angle_, CIRCLE_ANGLE);
    }
  }

  double Rectangle::getAngle() const noexcept
  {
    return angle_;
  }
}
