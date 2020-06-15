#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include "base-types.hpp"

namespace lovkacheva
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual void print(std::ostream& out) const = 0;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t& newPosition) = 0;

    virtual void move(double dx, double dy) = 0;

    virtual void scale(double coefficient) = 0;

    virtual void rotate(double angle) = 0;
  };
}
#endif
