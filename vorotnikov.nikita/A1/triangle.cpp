#include <string>
#include <stdexcept>
#include <cmath>
#include <algorithm>
#include "triangle.hpp"
#include "getLengthFunc.h"

Triangle::Triangle(const point_t &point_one, const point_t &point_two, const point_t &point_three) :
  point_one_(point_one),
  point_two_(point_two),
  point_three_(point_three),
  pos_({(point_one_.x + point_two_.x + point_three_.x) / 3, (point_one_.y + point_two_.y + point_three_.y) / 3 })
{
    if ( this->getArea() == 0 ) {
      throw std::invalid_argument(std::string("Invalid parameters: point shouldn't be equal or be on one line, point one (X,Y) = "
        + std::to_string(point_one_.x) + "," + std::to_string(point_one_.y) + ", point two (X,Y) = "
          + std::to_string(point_two_.x) + "," + std::to_string(point_two_.y) + ", point three (X,Y) = "
            + std::to_string(point_three_.x) + "," + std::to_string(point_three_.y)));
    }
}

double Triangle::getArea() const
{
  double half_perimetr = (getLength(point_one_, point_two_) + getLength(point_two_, point_three_)
    + getLength(point_one_, point_three_)) / 2;
  return sqrt(half_perimetr * (half_perimetr - getLength(point_one_, point_two_)) * (half_perimetr - getLength(point_two_, point_three_)))
    * (half_perimetr - getLength(point_one_, point_three_));
}

rectangle_t Triangle::getFrameRect() const
{
  double left = std::min(point_one_.x, std::min(point_two_.x, point_three_.x));
  double right = std::max(point_one_.x, std::max(point_two_.x, point_three_.x));
  double low = std::min(point_one_.y, std::min(point_two_.y, point_three_.y));
  double high = std::max(point_one_.y, std::max(point_two_.y, point_three_.y));
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
