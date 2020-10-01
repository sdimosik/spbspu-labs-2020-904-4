#include "triangle.hpp"
#include <cmath>
#include <algorithm>


point_t Triangle::calculateCentre()
{
  centre.x = (this->point_A.x + this->point_B.x + this->point_C.x)/3;
  centre.y = (this->point_A.y + this->point_B.y + this->point_C.y)/3;
  return centre;
}

Triangle::Triangle(const point_t &point_A, const point_t &point_B, const point_t &point_C):
  point_A(point_A),
  point_B(point_B),
  point_C(point_C)
{
  if (((point_A.x==point_B.x)&&(point_A.y==point_B.y))||((point_A.x == point_C.x)&&(point_A.y == point_C.y))||((point_B.x == point_C.x)&&(point_B.y==point_C.y)))
  {
    throw std::invalid_argument(std::string("Points can't be equal"));
  }
  if ((point_A.x == point_B.x) == point_C.x || (point_A.y == point_B.y) == point_C.y)
  {
      throw std::invalid_argument(std::string("Points can't be on the single line"));
  }
  calculateCentre();
}

double Triangle::getArea() const
{
  double area = 0;
  area = abs(0.5*((point_A.x - point_C.x)*(point_B.y-point_C.y)-(point_B.x - point_A.x)*(point_A.y-point_C.y)));
  return area;
}

point_t Triangle::getCentre() const
{
  return centre;
}

void Triangle::move(const double x, const double y)
{
  point_A.x += x;
  point_A.y += y;
  point_B.x += x;
  point_B.y += y;
  point_C.x += x;
  point_C.y += y;
  calculateCentre();
}

void Triangle::move(const point_t &point)
{
  move(point.x - centre.x, point.y - centre.y);
}

rectangle_t Triangle::getFrameRect() const
{
  double left = std::min({point_A.x, point_B.x, point_C.x});
  double right = std::max({point_A.x, point_B.x, point_C.x});
  double low = std::min({point_A.y, point_B.y, point_C.y});
  double high = std::max({point_A.y, point_B.y, point_C.y});
  return rectangle_t{ right - left, high - low, { (right + left) / 2, (high + low) / 2 } };
}

void Triangle::show() const
{
  std::cout << "Triangle's A(x,y) is: " << point_A.x << " " << point_A.y << '\n';
  std::cout << "Triangle's B(x,y) is: " << point_B.x << " " << point_B.y << '\n';
  std::cout << "Triangle's C(x,y) is: " << point_C.x << " " << point_C.y << '\n';
  std::cout << "Triangle's centre(x,y) is" << centre.x << " " << centre.y << '\n';
}

