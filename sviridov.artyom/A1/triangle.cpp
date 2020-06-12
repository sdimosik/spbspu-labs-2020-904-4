#include "triangle.hpp"
#include <cassert>
#include <cmath>
double Triangle::getArea() const
{
  double A = sqrt(pow(b_.x - a_.x, 2) + pow(b_.y - a_.y, 2));
  double B = sqrt(pow(c_.x - b_.x, 2) + pow(c_.y - b_.y, 2));
  double C = sqrt(pow(c_.x - a_.x, 2) + pow(c_.y - a_.y, 2));
  double halfperimetr = (A + B + C) / 2;
  double area = sqrt(halfperimetr * (halfperimetr - A) * (halfperimetr - B) * (halfperimetr - C));
  return area;
}

rectangle_t Triangle::getFrameRect() const
{
  double min_x = a_.x;
  if (min_x >= b_.x)
  {
    min_x = b_.x;
    if (min_x > c_.x)
     {
       min_x = c_.x;
     }
  }
  double min_y = a_.y;
  if (min_y >= b_.y)
  {
    min_y = b_.y;
    if (min_y > c_.y)
    {
      min_y = c_.y;
    }
  }
  return { {min_x + ((fabs(a_.x - b_.x) + fabs(a_.x - c_.x) + fabs(c_.x - b_.x)) / 4),
    min_y + ((fabs(a_.y - b_.y) + fabs(a_.y - c_.y) + fabs(c_.y - b_.y)) / 4)},
    (fabs(a_.x - b_.x) + fabs(a_.x - c_.x) + fabs(c_.x - b_.x)) / 2 ,
    (fabs(a_.y - b_.y) + fabs(a_.y - c_.y) + fabs(c_.y - b_.y)) / 2 };
}

Triangle::Triangle(const point_t& a, const point_t& b,const point_t& c) :
  Shape({ (a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3 }),
  a_(a),
  b_(b),
  c_(c)
{
  assert((a.x != b.x || a.x != c.x || b.x != c.x) && (a.y != b.y || a.y != c.y || b.y != c.y));
}

void Triangle::move(const point_t& end_pos)
{
  a_.x += (end_pos.x - pos_.x);
  a_.y += (end_pos.y - pos_.y);
  b_.x += (end_pos.x - pos_.x);
  b_.y += (end_pos.y - pos_.y);
  c_.x += (end_pos.x - pos_.x);
  c_.y += (end_pos.y - pos_.x);
  Shape::move(end_pos);
}

void Triangle::move(double dx, double dy)
{
  move({ pos_.x + dx, pos_.y + dy });
}

void Triangle::getInform(std::ostream& out) const
{
  out << "Triangle";
  Shape::getInform(out);
  out << "A: (" << a_.x << ";" << a_.y
    << ") B:(" << b_.x << ";" << b_.y
    << ") C:(" << c_.x << ";" << c_.y
    << ")";
}

std::ostream& operator<<(std::ostream& out, const Triangle& out_tri)
{
  out_tri.getInform(out);
  return out;
}
