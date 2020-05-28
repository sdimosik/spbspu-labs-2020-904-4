#include "shape.hpp"
#include<iostream>
void Shape::move(const point_t& pos)
{
  pos_ = pos;
}

void Shape::move(double dx, double dy)
{
  move({ dx + pos_.x, dy + pos_.y });
}

Shape::~Shape()
{
}

void Shape::getInform(std::ostream& out) const
{
  out << "(" << pos_.x << "," << pos_.y << ")";
}

Shape::Shape(const point_t& pos) :
   pos_(pos)
{
}

std::ostream& operator<<(std::ostream& out, const Shape& out_shape)
{
  out_shape.getInform(out);
  return out;
}

