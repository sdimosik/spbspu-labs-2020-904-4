
#include "rectangle.hpp"
#include <stdexcept>

namespace pashnin
{
  
  Rectangle::Rectangle(double width, double height, const point_t &dot) :
    width_(width),
    height_(height),
    position_(dot)
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument("Invalid argument(s) was(were) given.");
    }
  }
  
  double Rectangle::getArea() const
  {
    return width_ * height_;
  }
  
  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle_t{width_, height_, position_};
  }
  
  void Rectangle::move(const point_t &dot)
  {
    position_.x = dot.x;
    position_.y = dot.y;
  }
  
  void Rectangle::move(double xAxis, double yAxis)
  {
    position_.x += xAxis;
    position_.y += yAxis;
  }
  
  void Rectangle::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Invalid scale factor. Must be positive.");
    }
    width_ *= factor;
    height_ *= factor;
  }
  
}
