#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace meshcheryakov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(double dx, double dy) = 0;
    virtual void move(const point_t& point) = 0;
    virtual void scale(const double coefficient) = 0;
    virtual point_t getPosition() const noexcept = 0;
    virtual void rotate(const double angle) noexcept = 0;
  };
}
#endif
