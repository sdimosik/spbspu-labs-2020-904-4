#include "triangle.hpp"

#include <iostream>
#include <string>
#include <algorithm>

Triangle::Triangle(const point_t& vertex1, const point_t& vertex2, const point_t& vertex3) :
  vertex1_(vertex1),
  vertex2_(vertex2),
  vertex3_(vertex3)
{
  if (((vertex1_.x == vertex2_.x) && (vertex1_.x == vertex3.x))
      || ((vertex1_.y == vertex2_.y) && (vertex1_.y == vertex3_.y)))
  {
    throw std::invalid_argument("Invalid vertices value in triangle\n");
  }
}

rectangle_t Triangle::getFrameRect() const
{
  double min_x = std::min(std::min(vertex1_.x, vertex2_.x), vertex3_.x),
      max_x = std::max(std::max(vertex1_.x, vertex2_.x), vertex3_.x),
      min_y = std::min(std::min(vertex1_.y, vertex2_.y), vertex3_.y),
      max_y = std::max(std::max(vertex1_.y, vertex2_.y), vertex3_.y);
  return rectangle_t{ max_x - min_x, max_y - min_y, { (min_x + max_x) / 2, (min_y + max_y) / 2 }};
}

double Triangle::getArea() const
{
  return (abs(((vertex1_.x - vertex3_.x) * (vertex2_.y - vertex3_.y))
      - ((vertex2_.x - vertex3_.x) * (vertex1_.y - vertex3_.y))) / 2);
}

void Triangle::move(const double x, const double y)
{
  changVertexVal({ x, y });
}

void Triangle::move(const point_t& center)
{
  changVertexVal({ center.x - (vertex1_.x + vertex2_.x + vertex3_.x) / 3,
      center.y - (vertex1_.y + vertex2_.y + vertex3_.y) / 3 });
}

void Triangle::printData() const
{
  std::cout << "First vertex of the triangle : {" << vertex1_.x << ",  " << vertex1_.y
      << "}, Second vertex of the triangle : {" << vertex2_.x << ",  " << vertex2_.y
      << "}, Third vertex of the triangle : {" << vertex3_.x << ",  " << vertex3_.y << "}\n";
}

void Triangle::printFrameRectangle() const
{
  std::cout << "Rectangular triangle frame: height = " << getFrameRect().height
      << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
      << ", " << getFrameRect().pos.y << "}\n";
}

void Triangle::printArea() const
{
  std::cout << "Area of a triangle = " << getArea() << '\n';
}

void Triangle::changVertexVal(const point_t& pos)
{
  vertex1_.x += pos.x;
  vertex1_.y += pos.y;
  vertex2_.x += pos.x;
  vertex2_.y += pos.y;
  vertex3_.x += pos.x;
  vertex3_.y += pos.y;
}
