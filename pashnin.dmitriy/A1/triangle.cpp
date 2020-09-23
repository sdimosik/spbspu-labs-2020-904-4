
#include "triangle.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

double getDistance(const point_t &dot1, const point_t &dot2)
{
  return sqrt(pow(dot1.x - dot2.x, 2) + pow(dot1.y - dot2.y, 2));
}

Triangle::Triangle(const point_t &dot1, const point_t &dot2, const point_t &dot3) :
  top1_(dot1),
  top2_(dot2),
  top3_(dot3)
{
  if (top1_ == top2_ || top1_ == top3_ || top2_ == top3_)
  {
    throw std::invalid_argument("Error! 2 triangle tops can't be the same dot\n");
  }
  double side1 = getDistance(top1_, top2_),
      side2 = getDistance(top1_, top3_),
      side3 = getDistance(top2_, top3_);
  if (side1 + side2 == side3 || side1 + side3 == side2 || side2 + side3 == side1)
  {
    throw std::invalid_argument("Error! 3 triangle tops can't be on one straight line\n");
  }
}

double Triangle::getArea() const
{
  double side1 = getDistance(top1_, top2_),
      side2 = getDistance(top1_, top3_),
      side3 = getDistance(top2_, top3_),
      p = (side1 + side2 + side3) / 2;
  return sqrt(p * (p - side1) * (p - side2) * (p - side3));
}

rectangle_t Triangle::getFrameRect() const
{
  double xMin = std::min({top1_.x, top2_.x, top3_.x}),
      yMin = std::min({top1_.y, top2_.y, top3_.y}),
      xMax = std::max({top1_.x, top2_.x, top3_.x}),
      yMax = std::max({top1_.y, top2_.y, top3_.y}),
      width = xMax - xMin,
      height = yMax - yMin,
      xPoint = xMin + width / 2,
      yPoint = yMin + height / 2;
  return rectangle_t{width, height, point_t{xPoint, yPoint}};
}

void Triangle::move(double xAxis, double yAxis)
{
  top1_.x += xAxis;
  top2_.x += xAxis;
  top3_.x += xAxis;
  top1_.y += yAxis;
  top2_.y += yAxis;
  top3_.y += yAxis;
}

void Triangle::move(const point_t& dot)
{
  double xChange = (top1_.x + top2_.x + top3_.x) / 3 - dot.x,
      yChange = (top1_.y + top2_.y + top3_.y) / 3 - dot.y;
  move(xChange, yChange);
}
