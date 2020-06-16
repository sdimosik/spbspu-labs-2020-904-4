#include "rectangle.hpp"

namespace ushakov
{

  Rectangle::Rectangle(double width, double height, const point_t& pos) :
      width_(width),
      height_(height),
      pos_(pos)
  {
    if (width < 0)
    {
      throw std::invalid_argument("Invalid width of rectangle");
    }

    if (height < 0)
    {
      throw std::invalid_argument("Invalid height of rectangle");
    }
  }

  Rectangle::Rectangle(const rectangle_t& rectangle) :
      width_(rectangle.width),
      height_(rectangle.height),
      pos_(rectangle.pos)
  {}

  double Rectangle::getArea() const
  {
    return height_ * width_;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle_t{width_, height_, pos_};
  }

  void Rectangle::move(const point_t& point)
  {
    pos_ = point;
  }

  void Rectangle::move(double xAxis, double yAxis)
  {
    pos_.x += xAxis;
    pos_.y += yAxis;
  }

  point_t Rectangle::getPosition() const
  {
    return pos_;
  }

  double Rectangle::getWidth() const
  {
    return width_;
  }

  double Rectangle::getHeight() const
  {
    return height_;
  }

  void Rectangle::print() const
  {
    std::cout << "height = " << height_ << " width = " << width_ << " position.x = " << pos_.x
              << " position.y = " << pos_.y << std::endl;
  }

  void Rectangle::printFrameRectangle() const
  {
    std::cout << "height = " << height_ << " width = " << width_ << " center.x = " << pos_.x << " center.y = "
              << pos_.y << std::endl;
  }

  void Rectangle::scale(double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Invalid coefficient of scale, it must be positive");
    }

    width_ *= coefficient;
    height_ *= coefficient;
  }
}
