#include "circle.hpp"
#define _USE_MATH_DEFINES

#include <cmath>
#include <iostream>
#include <cassert>

Circle::Circle(const point_t& pos, double radius) :
  radius_(radius),
  pos_(pos)
{
  assert(radius > 0);
}

double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return { 2.0 * radius_, 2.0 * radius_, pos_ };
}

void Circle::move(const point_t& end_pos)
{
  pos_ = end_pos;
}

void Circle::move(double change_x, double change_y)
{
  pos_.x += change_x;
  pos_.y += change_y;
}

double Circle::getRadius() const
{
  return radius_;
}

double Circle::getCenterX() const
{
  return pos_.x;
}

double Circle::getCenterY() const
{
  return pos_.y;
}
