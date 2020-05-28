#include "triangle.hpp"
#include <stdexcept>
#include <cmath>

namespace anastasiev
{
  Triangle::Triangle(const point_t & a, const point_t & b, const point_t & c):
    a_(a),
    b_(b),
    c_(c),
    pos_{(a.x + b.x + c.x) / 3, (a.y + b.y + c.y) / 3 }
  {
    if (((c.x-a.x)/(b.x-a.x)==(c.y-a.y)/(b.y-a.y)))
    {
      throw std::invalid_argument("Triangle tops cannot be on straight line.");
    }
  }

  point_t Triangle::getPosition() const
  {
    return pos_;
  }  

  double Triangle::getArea() const
  {
    return (abs((b_.x - a_.x) * (c_.y - a_.y) - (c_.x -a_.x) * (b_.y - a_.y)))/2;
  }

  rectangle_t Triangle::getFrameRect() const
  {
    double minX = std::fmin(std::fmin(a_.x, b_.x), c_.x),
        maxX = std::fmax(std::fmax(a_.x, b_.x), c_.x),
        minY = std::fmin(std::fmin(a_.y, b_.y), c_.y),
        maxY = std::fmax(std::fmax(a_.y, b_.y), c_.y),
        width = maxX - minX,
        height = maxY - minY,
        posX = maxX - width/2,
        posY = maxY - height/2;
    return rectangle_t{width, height, point_t{posX,posY}};
  
  }
  void Triangle::move(const point_t & pos)
  {
    double dx = pos.x - pos_.x,
        dy = pos.y - pos_.y;
    this->move(dx, dy);
  }
  void Triangle::move(const double dx, const double dy)
  {
    pos_ = {pos_.x + dx, pos_.y + dy};
    a_ = {a_.x + dx, a_.y + dy};
    b_ = {b_.x + dx, b_.y + dy};
    c_ = {c_.x + dx, c_.y + dy};
  }
  void Triangle::scale(const double factor)
  {
    if (factor <= 0)
    {
      throw std::invalid_argument("Factor of scale must be positive.");
    }
    a_ = {pos_.x + (pos_.x - a_.x) * factor, pos_.y + (pos_.y - a_.y) * factor};
    b_ = {pos_.x + (pos_.x - b_.x) * factor, pos_.y + (pos_.y - b_.y) * factor};
    c_ = {pos_.x + (pos_.x - c_.x) * factor, pos_.y + (pos_.y - c_.y) * factor};
    
  }
}//namespace anastasiev
