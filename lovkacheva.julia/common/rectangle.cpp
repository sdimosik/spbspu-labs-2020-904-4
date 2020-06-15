#include "rectangle.hpp"
#include <cmath>

namespace lovkacheva
{
  Rectangle::Rectangle(const rectangle_t& contents) :
    contents_(contents),
    angle_(0)
  {
    if (contents.width <= 0)
    {
      throw std::invalid_argument(
          "The width of the rectangle must be positive (width = " + std::to_string(contents.width) + ")");
    }
    if (contents.height <= 0)
    {
      throw std::invalid_argument(
          "The height of the rectangle must be positive (height = " + std::to_string(contents.height) + ")");
    }
  }

  void Rectangle::print(std::ostream& out) const
  {
    out << "Rectangle (width = " << contents_.width << "; height = " << contents_.height
        << "; pos(" << contents_.pos.x << ", " << contents_.pos.y << "))";
    if (angle_)
    {
      std::cout << " rotated by the angle " << ((angle_ / M_PI) * 180);
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return (contents_.height * contents_.width);
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return rectangle_t{contents_.height * std::sin(angle_) + contents_.width * fabs(std::cos(angle_)),
        contents_.width * std::sin(angle_) + contents_.height * fabs(std::cos(angle_)), contents_.pos};
  }

  void Rectangle::move(const point_t& newPosition) noexcept
  {
    contents_.pos = newPosition;
  }

  void Rectangle::move(double dx, double dy) noexcept
  {
    contents_.pos.x += dx;
    contents_.pos.y += dy;
  }

  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0.0)
    {
      throw std::invalid_argument(
          "The coefficient must be positive (coefficient = " + std::to_string(coefficient) + ")");
    }
    contents_.width *= coefficient;
    contents_.height *= coefficient;
  }

  void Rectangle::rotate(double angle) noexcept
  {
    angle_ += (angle / 180) * M_PI;
    if (angle_ >= M_PI)
    {
      angle_ = fmod(angle_, M_PI);
    }
    else if ( angle_ < 0)
    {
      angle_ = M_PI + fmod(angle_, M_PI);
    }
  }
}
