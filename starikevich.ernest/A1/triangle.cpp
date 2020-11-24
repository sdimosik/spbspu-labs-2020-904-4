#include "triangle.hpp"
#include <stdexcept>
#include <cmath>
#include <iostream>
#include <string>
#include <algorithm>

Triangle::Triangle(const point_t& peak1, const point_t& peak2, const point_t& peak3) :
  peaks_{ peak1, peak2, peak3 }
{
  double side1 = std::sqrt((peaks_[0].x - peaks_[1].x) * (peaks_[0].x - peaks_[1].x) + (peaks_[0].y - peaks_[1].y) * (peaks_[0].y - peaks_[1].y)),
  side2 = std::sqrt((peaks_[1].x - peaks_[2].x) * (peaks_[1].x - peaks_[2].x) + (peaks_[1].y - peaks_[2].y) * (peaks_[1].y - peaks_[2].y)),
  side3 = std::sqrt((peaks_[2].x - peaks_[0].x) * (peaks_[2].x - peaks_[0].x) + (peaks_[2].y - peaks_[0].y) * (peaks_[2].y - peaks_[0].y));
  if (side1 + side2 <= side3 || side1 + side3 <= side2 || side3 + side2 <= side1)
  {
    throw std::invalid_argument("The sum of the two sides of the triangle must be greater than the third side. Sizes of the sides = "
      + std::to_string(side1) + "; " + std::to_string(side2) + "; " + std::to_string(side3) + ". Largest side = " + std::to_string(std::max(std::max(side1, side2), side3)));
  }
}

void Triangle::move(const point_t& pos)
{
  move(pos.x - getPosition().x, pos.y - getPosition().y);
}

void Triangle::move(double x, double y)
{
  for (size_t i = 0; i < 3; i++)
  {
    peaks_[i].x += x;
    peaks_[i].y += y;
  }
}

rectangle_t Triangle::getFrameRect() const
{
  double maxX = std::max({ peaks_[0].x, peaks_[1].x, peaks_[2].x}),
    minX = std::min({ peaks_[0].x, peaks_[1].x, peaks_[2].x}),
    maxY = std::max({ peaks_[0].y, peaks_[1].y, peaks_[2].y}),
    minY = std::min({ peaks_[0].y, peaks_[1].y, peaks_[2].y});
  return { maxX - minX, maxY - minY, {(maxX + minX) / 2, (maxY + minY) / 2} };
}

double Triangle::getSide1() const
{
  return std::sqrt((peaks_[1].x - peaks_[0].x) * (peaks_[1].x - peaks_[0].x) + (peaks_[1].y - peaks_[0].y) * (peaks_[1].y - peaks_[0].y));
}

double Triangle::getSide2() const
{
  return std::sqrt((peaks_[1].x - peaks_[2].x) * (peaks_[1].x - peaks_[2].x) + (peaks_[1].y - peaks_[2].y) * (peaks_[1].y - peaks_[2].y));
}

double Triangle::getSide3() const
{
  return std::sqrt((peaks_[2].x - peaks_[0].x) * (peaks_[2].x - peaks_[0].x) + (peaks_[2].y - peaks_[0].y) * (peaks_[2].y - peaks_[0].y));
}

point_t Triangle::getPosition() const
{
  return {(peaks_[0].x + peaks_[1].x + peaks_[2].x) / 3, (peaks_[0].y + peaks_[1].y + peaks_[2].y) / 3};
}

double Triangle::getArea() const
{
  double p = (getSide1() + getSide2() + getSide3()) / 2;
  double area = std::sqrt(p * (p - getSide1()) * (p - getSide2()) * (p - getSide3()));
  return area;
}
