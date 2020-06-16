#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace anastasiev
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const point_t &) noexcept = 0;
    virtual void move(const double, const double) noexcept = 0;
    virtual void scale(const double) = 0;
    virtual void rotate(double) noexcept = 0;
    virtual void rotateAroundPoint(double,const point_t&) noexcept = 0;
  };
} // namespace anastasiev
#endif
