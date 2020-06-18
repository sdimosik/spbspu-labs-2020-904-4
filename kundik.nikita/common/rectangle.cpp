#define _USE_MATH_DEFINES

#include <cmath>
#include "rectangle.hpp"
#include "base-types.hpp"
#include <iostream> 
#include <string>

const double HALF_CIRCLE = 180.0;

namespace kundik {
  Rectangle::Rectangle(const point_t& pos, double height, double width) :
    height_(height),
    width_(width),
    pos_(pos),
    angle_(0)
  {
    if (height <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid height value in rectangle  = ") += std::to_string(height));
    }

    if (width <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid width value in rectangle  = ") += std::to_string(width));
    }
  }

  double Rectangle::getArea() const
  {
    return (height_ * width_);
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return { width_, height_, pos_ };
  }

  void Rectangle::move(const point_t& end_pos)
  {
    pos_ = end_pos;
  }

  void Rectangle::move(double change_x, double change_y)
  {
    pos_.x += change_x;
    pos_.y += change_y;
  }

  double Rectangle::getHeight() const
  {
    return height_;
  }

  double Rectangle::getWidth() const
  {
    return width_;
  }

  double Rectangle::getCenterX() const
  {
    return(pos_.x);
  }

  double Rectangle::getCenterY() const
  {
    return(pos_.y);
  }

  void Rectangle::scale(double coefficent) 
  {
    if (coefficent <= 0.0)
    {
      throw std::invalid_argument(std::string("Invalid coefficent scaling value in rectangle = ") += std::to_string(coefficent));
    }
    height_ *= coefficent;
    width_ *= coefficent;
  }
  void Rectangle::rotate(double angle) noexcept
  {
    angle_ += angle * M_PI / HALF_CIRCLE;
    if (angle_ >= M_PI)
    {
      angle_ = fmod(angle_, M_PI);
    }
    else if (angle_ < 0)
    {
      angle_ = M_PI + fmod(angle_, M_PI);
    }
  }
}
