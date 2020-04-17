#include "rectangle.hpp"
#include <stdexcept>
#include <string>

namespace gromov
{
  Rectangle::Rectangle(const point_t& position, double width, double height):
    width_(width),
    height_(height),
    position_{position.x, position.y}
  {
    if(width <= 0 || height <= 0)
    {
      std::string str = "Height and Width must be positive,height = ";
      throw std::invalid_argument(std::string("Height and Width must be positive,height = " 
          + std::to_string(height_) + " ,width = "
          + std::to_string(width_)));
    }
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return rectangle_t{width_, height_, position_};
  }

  void Rectangle::move(const point_t& position) noexcept
  {
    position_ = position;
  }

  void Rectangle::move(const double x, const double y) noexcept
  {
    position_.x += x;
    position_.y += y;
  }

  double Rectangle::getArea() const noexcept
  {
    return(height_ * width_);
  }

  double Rectangle::getWidth() const noexcept
  {
    return width_;
  }

  double Rectangle::getHeight() const noexcept
  {
    return height_;
  }

  point_t Rectangle::getCentre() const noexcept
  {
    return position_;
  }
  void Rectangle::scale(const double cofficient)
  {
    if (cofficient <= 0)
    {
      throw std::invalid_argument(std::string("Coefficient must be positive = "
          + std::to_string(cofficient)));
    }
    height_ *= cofficient;
    width_ *= cofficient;
  }
}

