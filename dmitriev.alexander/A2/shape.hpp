#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace dmitriev
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &position) = 0;

    virtual void move(double x, double y) = 0;

    virtual void scale(double factor) = 0;
  };
}
#endif
