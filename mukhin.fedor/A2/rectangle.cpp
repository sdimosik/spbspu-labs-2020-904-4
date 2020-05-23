#include "rectangle.hpp"
#include <stdexcept>
#include <string>
 
namespace mukhin
{
  Rectangle::Rectangle(const double width, const double height, const point_t& core) :
    pos_(core),
    width_(width),
    height_(height)
  {
    if (height <= 0 || width <= 0)
    {
      throw std::invalid_argument(std::string("Height and width must be positive numbers! Height:"
          + std::to_string(height) + " Width: "
          + std::to_string(width)));
    }
  }

  double Rectangle::getArea() const
  {
    return width_ * height_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return { pos_, width_, height_ };
  }

  void Rectangle::move(const double dx, const double dy)
  {
    pos_.x += dx;
    pos_.y += dy;
  }
 
  void Rectangle::move(const point_t& core)
  {
    pos_ = core;
  }

  void Rectangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument(std::string("Factor must be a positive number! Factor: "
          + std::to_string(factor)));
    }
    height_ *= factor;
    width_ *= factor;
  }
 
  point_t Rectangle::getCore() const
  {
    return pos_;
  }

  double Rectangle::getHeight() const
  {
    return height_;
  }

  double Rectangle::getWidth() const
  {
    return width_;
  }
}
