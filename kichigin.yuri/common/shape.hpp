#ifndef SHAPE
#define SHAPE

#include "base-types.hpp"

namespace kichigin
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const point_t& point) noexcept = 0;
    virtual void move(double x, double y) noexcept = 0;
    virtual void scale(double coefficient) = 0;
  };
}

#endif//!SHAPE
