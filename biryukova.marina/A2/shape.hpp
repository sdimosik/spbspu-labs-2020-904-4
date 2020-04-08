#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace biryukova
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual biryukova::rectangle_t getFrameRect() const = 0;
    virtual void move(const biryukova::point_t& point) = 0;
    virtual void move(double x, double y) = 0;
    virtual void print() const = 0;
    virtual void scale(double coefficient) = 0;
  };
}

#endif
