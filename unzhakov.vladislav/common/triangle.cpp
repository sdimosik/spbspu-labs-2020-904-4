#include "triangle.hpp"

#include <iostream>
#include <algorithm>
#include <cmath>

unzhakov::Triangle::Triangle(const unzhakov::point_t &vertex1, const unzhakov::point_t &vertex2,
    const unzhakov::point_t &vertex3):
  vertex1_(vertex1),
  vertex2_(vertex2),
  vertex3_(vertex3),
  center_({(vertex1.x + vertex2.x + vertex3.x) / 3, (vertex1.y + vertex2.y + vertex3.y) / 3})
{
  if (((vertex1_.x == vertex2_.x) && (vertex1_.x == vertex3.x))
      || ((vertex1_.y == vertex2_.y) && (vertex1_.y == vertex3_.y)))
  {
    throw std::invalid_argument("Invalid vertices value in triangle\n");
  }
}

unzhakov::rectangle_t unzhakov::Triangle::getFrameRect() const
{
  const double min_x = std::min(std::min(vertex1_.x, vertex2_.x), vertex3_.x),
      max_x = std::max(std::max(vertex1_.x, vertex2_.x), vertex3_.x),
      min_y = std::min(std::min(vertex1_.y, vertex2_.y), vertex3_.y),
      max_y = std::max(std::max(vertex1_.y, vertex2_.y), vertex3_.y);
  return unzhakov::rectangle_t{max_x - min_x, max_y - min_y, {(min_x + max_x) / 2, (min_y + max_y) / 2}};
}

double unzhakov::Triangle::getArea() const
{
  return (
    fabs(((vertex1_.x - vertex3_.x) * (vertex2_.y - vertex3_.y))
        - ((vertex2_.x - vertex3_.x) * (vertex1_.y - vertex3_.y))) / 2);
}

unzhakov::point_t unzhakov::Triangle::getCenter() const
{
  return center_;
}

void unzhakov::Triangle::move(const double x, const double y)
{
  changVertexVal({x, y});
}

void unzhakov::Triangle::move(const unzhakov::point_t &center)
{
  changVertexVal({center.x - center_.x, center.y - center_.y});
}

void unzhakov::Triangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient in triangle = " + std::to_string(coefficient) + '\n');
  }
  vertex1_ = {(vertex1_.x - center_.x) * coefficient + center_.x,
                (vertex1_.y - center_.y) * coefficient + center_.y};
  vertex2_ = {(vertex2_.x - center_.x) * coefficient + center_.x,
                (vertex2_.y - center_.y) * coefficient + center_.y};
  vertex3_ = {(vertex3_.x - center_.x) * coefficient + center_.x,
                (vertex3_.y - center_.y) * coefficient + center_.y};
}

void unzhakov::Triangle::printData() const
{
  std::cout << "First vertex of the triangle : {" << vertex1_.x << ",  " << vertex1_.y
      << "}, Second vertex of the triangle : {" << vertex2_.x << ",  " << vertex2_.y
      << "}, Third vertex of the triangle : {" << vertex3_.x << ",  " << vertex3_.y << "}\n";
}

void unzhakov::Triangle::printFrameRectangle() const
{
  std::cout << "Rectangular triangle frame: height = " << getFrameRect().height
      << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
      << ", " << getFrameRect().pos.y << "}\n";
}

void unzhakov::Triangle::printArea() const
{
  std::cout << "Area of a triangle = " << getArea() << '\n';
}

void unzhakov::Triangle::changVertexVal(const unzhakov::point_t &pos)
{
  vertex1_.x += pos.x;
  vertex1_.y += pos.y;
  vertex2_.x += pos.x;
  vertex2_.y += pos.y;
  vertex3_.x += pos.x;
  vertex3_.y += pos.y;

}
