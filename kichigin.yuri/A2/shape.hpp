#ifndef SHAPE
#define SHAPE

#include "base-types.hpp"

namespace kichigin
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& point) = 0;
    virtual void move(double x, double y) = 0;
    virtual void scale(double coefficient) = 0;
  };
}

#endif//!SHAPE
