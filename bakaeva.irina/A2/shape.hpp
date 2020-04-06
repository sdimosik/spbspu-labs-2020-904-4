#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace bakaeva
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &center) = 0;

    virtual void move(const double x, const double y) = 0;

    virtual void printData() const = 0;

    virtual void printFrameRect() const = 0;

    virtual void scale(const double coefficient) = 0;
  };
}

#endif
