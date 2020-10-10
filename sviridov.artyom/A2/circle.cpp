#define _USE_MATH_DEFINES
#include "circle.hpp"
#include <iostream>
#include <cmath>
namespace sviridov
{
  double Circle::getArea() const
  {
    return rad_ * rad_ * M_PI;
  }

  rectangle_t Circle::getFrameRect() const
  {
    return { pos_, 2 * rad_, 2 * rad_ };
  }

  Circle::Circle(const point_t &pos, double r) :
        pos_(pos),
        rad_(r)
  {
    if (rad_ <= 0)
    {
      throw std::invalid_argument("Not correct arguments for construct circle");
    }
  }

  void Circle::printInform(std::ostream& out) const
  {
    out << "Circle " << "pos = " << pos_.x << " "
        << pos_.y << " radius = " << rad_;
  }

  std::ostream& operator<<(std::ostream& out, const Circle& out_circle)
  {
    out_circle.printInform(out);
    return out;
  }

  void Circle::move(const point_t &pos)
  {
    pos_ = pos;
  }

  void Circle::move(double dx, double dy)
  {
    pos_ = {pos_.x + dx, pos_.y + dy};
  }


  void Circle::scale(double coefficient)
  {
    if ((coefficient > 0) && (coefficient != 1))
    {
      rad_ *= coefficient;
    }
    else if(coefficient != 1)
     {
       throw std::invalid_argument("No correct arguments for scale circle");
     }
  }
}
