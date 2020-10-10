#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include "base-types.hpp"
namespace sviridov
{
  class Shape
  {
  public:
    friend std::ostream& operator<<(std::ostream&, const Shape&);
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t&) = 0;
    virtual void move(double, double) = 0;
    virtual ~Shape() =  default;
    virtual void printInform(std::ostream&) const = 0;
    virtual void scale(double) = 0;
  };
  std::ostream& operator<<(std::ostream&, const Shape&);
}
#endif
