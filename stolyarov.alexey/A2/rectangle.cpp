#include "rectangle.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

namespace stolyarov
{
  Rectangle::Rectangle(double width, double height, const point_t& pos) :
    Shape(pos),
    width_(width),
    height_(height)
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

  void Rectangle::move(double x, double y)
  {
    pos_.x += x;
    pos_.y += y;
  }

  void Rectangle::move(const point_t& pos)
  {
    pos_ = pos;
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle_t({ width_, height_, pos_ });
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
}
