#include "rectangle.hpp"
#include <iostream>
#include <string>
#include <stdexcept>

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
  std::cout << "Rectangle information" << std::endl
      << "Center's location:" << std::endl
      << "x: " << pos_.x << std::endl << "y: " << pos_.y << std::endl
      << "Parameters of the rectangle:" << std::endl
      << "height: " << height_ << std::endl << "widht: " << width_ << std::endl
      << "Area of the rectangle: " << getArea() << std::endl << std::endl;
}

void Rectangle::printFrameInf()
{
  std::cout << "Frame information" << std::endl
      << "Center's location:" << std::endl
      << "x: " << getFrameRect().pos.x << std::endl << "y: " << getFrameRect().pos.y << std::endl
      << "Parameters of the frame:" << std::endl
      << "height: " << getFrameRect().height << std::endl << "widht: " << getFrameRect().width << std::endl << std::endl;
}
