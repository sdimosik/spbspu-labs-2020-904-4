#include "triangle.hpp"
#include <string>
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t &point1, const point_t &point2, const point_t &point3) :
  point1_(point1),
  point2_(point2),
  point3_(point3),
  pos_({(point1_.x + point2_.x + point3_.x) / 3, (point1_.y + point2_.y + point3_.y) / 3 }),
  side1(sqrt((pow((abs(point2_.x) - abs(point1_.x)), 2) + pow((abs(point2_.y) - abs(point1_.y)), 2)))),
  side2(sqrt((pow((abs(point3_.x) - abs(point2_.x)), 2) + pow((abs(point3_.y) - abs(point2_.y)), 2)))),
  side3(sqrt((pow((abs(point3_.x) - abs(point1_.x)), 2) + pow((abs(point3_.y) - abs(point1_.y)), 2))))
{}

double Triangle::getArea() const
{
  double half_perimetr = (side1 + side2 + side3) / 2;
  return sqrt(half_perimetr * (half_perimetr - side1) * (half_perimetr - side2) * (half_perimetr - side3));
}

rectangle_t Triangle::getFrameRect() const
{
  double left = 0.0, right = 0.0, high = 0.0, low = 0.0;
  if ((point1_.x < point2_.x) && (point1_.x < point3_.x)) {
    left = point1_.x;
  } else if ((point2_.x < point1_.x) && (point2_.x < point3_.x)) {
    left = point2_.x;
  } else if ((point3_.x < point1_.x) && (point3_.x < point2_.x)) {
    left = point3_.x;
  }

  if ((point1_.y < point2_.y) && (point1_.y < point3_.y)) {
    low = point1_.y;
  } else if ((point2_.y < point1_.y) && (point2_.y < point3_.y)) {
    low = point2_.y;
  } else if ((point3_.y < point1_.y) && (point3_.y < point2_.y)) {
    low = point3_.y;
  }

  if ((point1_.x > point2_.x) && (point1_.x > point3_.x)) {
    right = point1_.x;
  } else if ((point2_.x > point1_.x) && (point2_.x > point3_.x)) {
    right = point2_.x;
  } else if ((point3_.x > point1_.x) && (point3_.x > point2_.x)) {
    right = point3_.x;
  }

  if ((point1_.y > point2_.y) && (point1_.y > point3_.y)) {
    high = point1_.y;
  } else if ((point2_.y > point1_.y) && (point2_.y > point3_.y)) {
    high = point2_.y;
  } else if ((point3_.y > point1_.y) && (point3_.y > point2_.y)) {
    high = point3_.y;
  }

  return rectangle_t{ std::abs(right) - std::abs(left), std::abs(high) - std::abs(low), { ((2 * right) + (2 * left)) / 4, ((2 * high) + (2 * low)) / 4 } };
}

void Triangle::move(const point_t &point)
{
  move(point.x - pos_.x, point.y - pos_.y);
}

void Triangle::move(double x, double y)
{
  point1_.x += x;
  point1_.y += y;
  point2_.x += x;
  point2_.y += y;
  point3_.x += x;
  point3_.y += y;
  pos_.x += x;
  pos_.y += y;
}

double Triangle::getCenterX()
{
  return pos_.x;
}

double Triangle::getCenterY()
{
  return pos_.y;
}
