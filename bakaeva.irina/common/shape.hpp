#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace bakaeva
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const noexcept = 0;

    virtual rectangle_t getFrameRect() const noexcept = 0;

    virtual void move(const point_t &center) noexcept = 0;

    virtual void move(const double x, const double y) noexcept = 0;

    virtual void printData() const = 0;

    virtual void printFrameRect() const = 0;

    virtual void scale(const double coefficient) = 0;
  };
}

#endif
