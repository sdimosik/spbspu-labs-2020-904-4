
#include "circle.hpp"
#include <stdexcept>
#include <cmath>

namespace pashnin
{
  
  Circle::Circle(double radius, const point_t &dot) :
    radius_(radius),
    position_(dot)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("Invalid argument was given.");
    }
  }
  
  double Circle::getArea() const
  {
    return M_PI * radius_ * radius_;
  }
  
  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{radius_ * 2, radius_ * 2, position_};
  }
  
  void Circle::move(const point_t &dot)
  {
    position_ = dot;
  }
  
  void Circle::move(double xAxis, double yAxis)
  {
    position_.x += xAxis;
    position_.y += yAxis;
  }
  
  void Circle::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Invalid scale factor. Must be positive.");
    }
    radius_ *= factor;
  }
  
  void Circle::rotate(const double) noexcept
  {
  
  }
  
}
