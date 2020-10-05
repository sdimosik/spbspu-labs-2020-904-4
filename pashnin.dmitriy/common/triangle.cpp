
#include "triangle.hpp"
#include "specs.hpp"
#include <stdexcept>
#include <cmath>
#include <algorithm>

namespace pashnin
{
  
  double getDistance(const point_t &dot1, const point_t &dot2)
  {
    return sqrt(pow(dot1.x - dot2.x, 2) + pow(dot1.y - dot2.y, 2));
  }
  
  Triangle::Triangle(const point_t &dot1, const point_t &dot2, const point_t &dot3) :
    top1_(dot1),
    top2_(dot2),
    top3_(dot3),
    angle_(0.0)
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
  
  double Triangle::getCenterX() const {
    return (top1_.x + top2_.x + top3_.x) / 3;
  }
  
  double Triangle::getCenterY() const {
    return (top1_.y + top2_.y + top3_.y) / 3;
  }
  
  point_t Triangle::getTop1() const {
    return top1_;
  }
  
  point_t Triangle::getTop2() const {
    return top2_;
  }
  
  point_t Triangle::getTop3() const {
    return top3_;
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
  
  void Triangle::move(const point_t &dot)
  {
    double xChange = getCenterX() - dot.x,
      yChange = getCenterY() - dot.y;
    move(xChange, yChange);
  }
  
  void changeTopScaling(point_t &top, const point_t &center, double factor)
  {
    int xMax = std::max(top.x, center.x),
        xMin = std::min(top.x, center.x),
        yMax = std::max(top.y, center.y),
        yMin = std::min(top.y, center.y);
    if (top.x > center.x)
    {
      top.x = xMax + (xMax - xMin)*(factor - 1);
    }
    else
    {
      top.x = xMin + (xMax - xMin)*(factor - 1);
    }
    
    if (top.y > center.y)
    {
      top.y = yMax + (yMax - yMin)*(factor - 1);
    }
    else
    {
      top.y = yMin + (yMax - yMin)*(factor - 1);
    }
  }
  
  void Triangle::scale(double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Invalid scale factor. Must be positive.");
    }
    point_t center {0, 0};
    center.x = (top1_.x + top2_.x + top3_.x) / 3;
    center.y = (top1_.y + top2_.y + top3_.y) / 3;
    changeTopScaling(top1_, center, factor);
    changeTopScaling(top2_, center, factor);
    changeTopScaling(top3_, center, factor);
  }
  
  void Triangle::rotate(double angle) noexcept
  {
    angle_ = specs::changeAngle(angle_, angle);
    point_t* tops[3] = {&top1_, &top2_, &top3_};
    double centerX = (top1_.x + top2_.x + top3_.x) / 3;
    double centerY = (top1_.y + top2_.y + top3_.y) / 3;
    for(point_t* top : tops)
    {
      double tempX = top->x;
      top->x = (top->x - centerX) * cos(angle_) - (top->y - centerY) * sin(angle_) + centerX;
      top->y = (tempX - centerX) * sin(angle_) + (top->y - centerY) * cos(angle_) + centerY;
    }
  }
  
}
