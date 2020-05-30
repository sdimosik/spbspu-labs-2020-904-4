#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace khilchenko
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t &newPos) noexcept = 0;
    virtual void move(double x, double y) noexcept = 0;
    virtual point_t getCenter() const noexcept = 0;
    virtual void scale(double coefficient) = 0;
  };
}
#endif
