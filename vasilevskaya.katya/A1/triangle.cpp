#include <iostream>
#include "triangle.hpp"
#include <algorithm>
#include <cmath>
#include "base-types.hpp"

Triangle::Triangle(const point_t& a, const point_t& b, const point_t& c) :
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

double Triangle::getArea() const
{
  return (abs((b_.x - a_.x) * (c_.y - a_.y) - (c_.x - a_.x) * (b_.y - a_.y))) / 2;
}

rectangle_t Triangle::getFrameRect() const
{
  double minX = std::fmin(std::fmin(a_.x, b_.x), c_.x),
    maxX = std::fmax(std::fmax(a_.x, b_.x), c_.x),
    minY = std::fmin(std::fmin(a_.y, b_.y), c_.y),
    maxY = std::fmax(std::fmax(a_.y, b_.y), c_.y),
    width = maxX - minX,
    height = maxY - minY,
    posX = maxX - width / 2,
    posY = maxY - height / 2;
  return rectangle_t{ width, height, point_t{posX,posY} };

}

point_t Triangle::getPosition() const
{
  return pos_;
}

void Triangle::move(const point_t& pos)
{
  double dx = pos.x - pos_.x,
    dy = pos.y - pos_.y;
  pos_ = pos;
  a_ = { a_.x + dx, a_.y + dy };
  b_ = { b_.x + dx, b_.y + dy };
  c_ = { c_.x + dx, c_.y + dy };

}
void Triangle::move(const double dx, const double dy)
{
  pos_ = { pos_.x + dx, pos_.y + dy };
  a_ = { a_.x + dx, a_.y + dy };
  b_ = { b_.x + dx, b_.y + dy };
  c_ = { c_.x + dx, c_.y + dy };
}

void Triangle::printFigure() const
{
  std::cout << "it is Triangle\n"
    << "Position of frame" << getFrameRect().pos.x << ";" << getFrameRect().pos.y << '\n'
    << "\nHeight : " << getFrameRect().height
    << "\nWidth : " << getFrameRect().width;

}
