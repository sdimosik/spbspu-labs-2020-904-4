#include "triangle.hpp"
#include <string>
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t &point_one, const point_t &point_two, const point_t &point_three) :
  point_one_(point_one),
  point_two_(point_two),
  point_three_(point_three),
  pos_({(point_one_.x + point_two_.x + point_three_.x) / 3, (point_one_.y + point_two_.y + point_three_.y) / 3 }),
  side_one_(sqrt((pow((abs(point_two_.x) - abs(point_one_.x)), 2) + pow((abs(point_two_.y) - abs(point_one_.y)), 2)))),
  side_two_(sqrt((pow((abs(point_three_.x) - abs(point_two_.x)), 2) + pow((abs(point_three_.y) - abs(point_two_.y)), 2)))),
  side_three_(sqrt((pow((abs(point_three_.x) - abs(point_one_.x)), 2) + pow((abs(point_three_.y) - abs(point_one_.y)), 2))))
{}

double Triangle::getArea() const
{
  double half_perimetr = (side_one_ + side_two_ + side_three_) / 2;
  return sqrt(half_perimetr * (half_perimetr - side_one_) * (half_perimetr - side_two_) * (half_perimetr - side_three_));
}

rectangle_t Triangle::getFrameRect() const
{
  double left = 0.0, right = 0.0, high = 0.0, low = 0.0;
  if ((point_one_.x < point_two_.x) && (point_one_.x <point_three_.x)) {
    left = point_one_.x;
  } else if ((point_two_.x < point_one_.x) && (point_two_.x < point_three_.x)) {
    left = point_two_.x;
  } else if ((point_three_.x < point_one_.x) && (point_three_.x < point_two_.x)) {
    left = point_three_.x;
  }

  if ((point_one_.y < point_two_.y) && (point_one_.y < point_three_.y)) {
    low = point_one_.y;
  } else if ((point_two_.y < point_one_.y) && (point_two_.y < point_three_.y)) {
    low = point_two_.y;
  } else if ((point_three_.y < point_one_.y) && (point_three_.y < point_two_.y)) {
    low = point_three_.y;
  }

  if ((point_one_.x > point_two_.x) && (point_one_.x > point_three_.x)) {
    right = point_one_.x;
  } else if ((point_two_.x > point_one_.x) && (point_two_.x > point_three_.x)) {
    right = point_two_.x;
  } else if ((point_three_.x > point_one_.x) && (point_three_.x > point_two_.x)) {
    right = point_three_.x;
  }

  if ((point_one_.y > point_two_.y) && (point_one_.y > point_three_.y)) {
    high = point_one_.y;
  } else if ((point_two_.y > point_one_.y) && (point_two_.y > point_three_.y)) {
    high = point_two_.y;
  } else if ((point_three_.y > point_one_.y) && (point_three_.y > point_two_.y)) {
    high = point_three_.y;
  }

  return rectangle_t{ right - left, high - low, { (right + left) / 2, (high + low) / 2 } };
}

void Triangle::move(const point_t &point)
{
  move(point.x - pos_.x, point.y - pos_.y);
}

void Triangle::move(double x, double y)
{
  point_one_.x += x;
  point_one_.y += y;
  point_two_.x += x;
  point_two_.y += y;
  point_three_.x += x;
  point_three_.y += y;
  pos_.x += x;
  pos_.y += y;
}

double Triangle::getCenterX() const
{
  return pos_.x;
}

double Triangle::getCenterY() const
{
  return pos_.y;
}
