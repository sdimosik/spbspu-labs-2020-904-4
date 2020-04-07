#include "rectangle.hpp"
#include "base-types.hpp"
#include <iostream> 
#include <cassert>

Rectangle::Rectangle(const point_t& pos, double height, double width) :
  height_(height),
  width_(width),
  pos_(pos)
{
  assert(height > 0 && width > 0);
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
