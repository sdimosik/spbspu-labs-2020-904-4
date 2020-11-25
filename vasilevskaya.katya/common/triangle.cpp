#define _USE_MATH_DEFINES
#include <iostream>
#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include "base-types.hpp"

const int FULL_CIRCLE = 180;



vasilevskaya::Triangle::Triangle(const point_t& a, const point_t& b, const point_t& c) :
  a_(a),
  b_(b),
  c_(c),
  pos_{ (a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3 }
{
  if (((c.x - a.x) / (b.x - a.x) == (c.y - a.y) / (b.y - a.y)) || ((a.x == b.x) && (a.y == b.y)) ||
    ((a.x == c.x) && (a.y == c.y)) || ((c.x == b.x) && (c.y == b.y)))
  {
    throw std::invalid_argument("Triangle tops cannot be on straight line or in one dot.");
  }
}

double vasilevskaya::Triangle::getArea() const
{
  return (abs((b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y))) / 2;
}

vasilevskaya::rectangle_t vasilevskaya::Triangle::getFrameRect() const
{
  double minX = std::fmin(std::fmin(a_.x, b_.x), c_.x),
    maxX = std::fmax(std::fmax(a_.x, b_.x), c_.x),
    minY = std::fmin(std::fmin(a_.y, b_.y), c_.y),
    maxY = std::fmax(std::fmax(a_.y, b_.y), c_.y),
    width = maxX - minX,
    height = maxY - minY,
    posX = maxX - width / 2,
    posY = maxY - height / 2;
  return vasilevskaya::rectangle_t{ width, height, point_t{posX,posY} };

}

vasilevskaya::point_t vasilevskaya::Triangle::getPosition() const
{
  return pos_;
}

void vasilevskaya::Triangle::move(const point_t& pos)
{
  double dx = pos.x - pos_.x,
    dy = pos.y - pos_.y;
  pos_ = pos;
  a_ = { a_.x + dx, a_.y + dy };
  b_ = { b_.x + dx, b_.y + dy };
  c_ = { c_.x + dx, c_.y + dy };

}
void vasilevskaya::Triangle::move(const double dx, const double dy)
{
  pos_ = { pos_.x + dx, pos_.y + dy };
  a_ = { a_.x + dx, a_.y + dy };
  b_ = { b_.x + dx, b_.y + dy };
  c_ = { c_.x + dx, c_.y + dy };
}

void vasilevskaya::Triangle::printFigure() const
{
  std::cout << "it is Triangle\n"
    << "Position of frame" << getFrameRect().pos.x << ";" << getFrameRect().pos.y << '\n'
    << "\nHeight : " << getFrameRect().height
    << "\nWidth : " << getFrameRect().width;

}

void vasilevskaya::Triangle::printFrameRect() const
{
  rectangle_t rect = getFrameRect();

  std::cout << "height = " << rect.height
    << " width = " << rect.width
    << " center.x = " << rect.pos.x
    << " center.y = " << rect.pos.y << std::endl;
}

void vasilevskaya::Triangle::scale(double quotient)
{
  if (quotient <= 0)
  {
    throw std::invalid_argument("The quotient must be greater or equal than zero");
  }
  a_ = { pos_.x + (pos_.x - a_.x) * quotient, pos_.y + (pos_.y - a_.y) * quotient };
  b_ = { pos_.x + (pos_.x - b_.x) * quotient, pos_.y + (pos_.y - b_.y) * quotient };
  c_ = { pos_.x + (pos_.x - c_.x) * quotient, pos_.y + (pos_.y - c_.y) * quotient };
}

void vasilevskaya::Triangle::rotate(double angle)
{

  const double angleInRadians = angle * M_PI / FULL_CIRCLE;
  const double sinValue = std::sin(angleInRadians);
  const double cosValue = std::cos(angleInRadians);
  const point_t position = getPosition();

  for (point_t& top : tops_)
  {
    const double previousX = top.x;

    top.x = position.x + (top.x - position.x) * cosValue - (top.y - position.y) * sinValue;
    top.y = position.y + (top.y - position.y) * cosValue + (previousX - position.x) * sinValue;
  }
}
