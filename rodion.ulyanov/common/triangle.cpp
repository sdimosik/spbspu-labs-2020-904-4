#include "triangle.hpp"
#include <cmath>
#include <algorithm>
#include "optional.hpp"
namespace rodion
{
point_t Triangle::calculateCentre() {
  centre.x = (this->point_A.x + this->point_B.x + this->point_C.x) / 3;
  centre.y = (this->point_A.y + this->point_B.y + this->point_C.y) / 3;
  return centre;
}

point_t Triangle::getPointA() const {
  return point_A;
}

point_t Triangle::getPointB() const {
  return point_B;
}

point_t Triangle::getPointC() const {
  return point_C;
}


Triangle::Triangle(const point_t &point_A, const point_t &point_B, const point_t &point_C) :
    point_A(point_A),
    point_B(point_B),
    point_C(point_C) {
  if (((point_A.x == point_B.x) && (point_A.y == point_B.y)) ||
      ((point_A.x == point_C.x) && (point_A.y == point_C.y)) ||
      ((point_B.x == point_C.x) && (point_B.y == point_C.y))) {
    throw std::invalid_argument(std::string("Points can't be equal"));
  }
  if ((point_A.x == point_B.x) == point_C.x || (point_A.y == point_B.y) == point_C.y) {
    throw std::invalid_argument(std::string("Points can't be on the single line"));
  }
  calculateCentre();
}

double Triangle::getArea() const
{
  const double A = optional::getDistance(point_A,point_B);
  const double B = optional::getDistance(point_B,point_C);
  const double C = optional::getDistance(point_C,point_A);
  double half_p = (A+B+C)/2;
  return (sqrt(half_p * (half_p - A) * (half_p - B) * (half_p - C)));
}

point_t Triangle::getCentre() const {
  return centre;
}

void Triangle::move(const double x, const double y) {
  point_A.x += x;
  point_A.y += y;
  point_B.x += x;
  point_B.y += y;
  point_C.x += x;
  point_C.y += y;
  calculateCentre();
}

void Triangle::move(const point_t &point) {
  move(point.x - centre.x, point.y - centre.y);
}

rectangle_t Triangle::getFrameRect() const
{
  double left = std::min({point_A.x, point_B.x, point_C.x});
  double right = std::max({point_A.x, point_B.x, point_C.x});
  double low = std::min({point_A.y, point_B.y, point_C.y});
  double high = std::max({point_A.y, point_B.y, point_C.y});
  return rectangle_t{right - left, high - low, {(right + left) / 2, (high + low) / 2}};
}

void Triangle::show() const {
  std::cout << "Triangle's A(x,y) is: " << point_A.x << " " << point_A.y << '\n';
  std::cout << "Triangle's B(x,y) is: " << point_B.x << " " << point_B.y << '\n';
  std::cout << "Triangle's C(x,y) is: " << point_C.x << " " << point_C.y << '\n';
  std::cout << "Triangle's centre(x,y) is" << centre.x << " " << centre.y << '\n';
}

void Triangle::scale(double value)
{
  if (value <= 0) {
    throw std::invalid_argument(std::string("Value must be positive, value = "
                                            + std::to_string(value)));
  }
  point_A.x -= (value - 1) * (centre.x - point_A.x);
  point_B.x -= (value - 1) * (centre.x - point_B.x);
  point_C.x -= (value - 1) * (centre.x - point_C.x);
  point_A.y -= (value - 1) * (centre.y - point_A.y);
  point_B.y -= (value - 1) * (centre.y - point_B.y);
  point_C.y -= (value - 1) * (centre.y - point_C.y);
}

void Triangle::rotate(double angle) noexcept
{
  const double angleRad = optional::performToRadians(angle);
  const double sin = std::sin(angleRad),
    cos = std::cos(angleRad);
  point_t* points[3] = {&point_A, &point_B, &point_C};
   for(point_t* point : points)
  {
    const double distanceX = point -> x - centre.x;
    const double distanceY = point -> y - centre.y;
    point -> x = centre.x + distanceX * cos - distanceY * sin;
    point -> y = centre.y + distanceX * sin + distanceY * cos;
  }
 }
 

};
