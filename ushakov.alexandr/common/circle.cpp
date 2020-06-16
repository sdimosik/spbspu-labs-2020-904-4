#include "circle.hpp"
#include <cmath>
#include <stdexcept>

namespace ushakov
{

  Circle::Circle(const point_t& center, double radius) :
      pos_(center),
      radius_(radius)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("Invalid radius");
    }
  }

  double Circle::getArea() const
  {
    return M_PI * radius_ * radius_;
  }

  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{2 * radius_, 2 * radius_, pos_};
  }

  void Circle::move(const point_t& point)
  {
    pos_ = point;
  }

  void Circle::move(double xAxis, double yAxis)
  {
    pos_.x += xAxis;
    pos_.y += yAxis;
  }

  point_t Circle::getPosition() const
  {
    return pos_;
  }

  double Circle::getRadius() const
  {
    return radius_;
  }

  void Circle::print() const
  {
    std::cout << "radius = " << radius_ << " center.x = " << pos_.x << " center.y = " << pos_.y << std::endl;
  }

  void Circle::printFrameRectangle() const
  {
    rectangle_t rect = getFrameRect();

    std::cout << "height = " << rect.height << " width = " << rect.width << " center.x = " << rect.pos.x
              << " center.y = "
              << rect.pos.y << std::endl;
  }

  void Circle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Invalid coefficient of scale, it must be positive");
    }

    radius_ *= coefficient;
  }
}
