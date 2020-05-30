#ifndef SHAPE_H
#define SHAPE_H
#include "base-types.h"

namespace  vorotnikov {
  class Shape {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const = 0;

    virtual rectangle_t getFrameRect() const = 0;

    virtual void move(const point_t &pos) = 0;

    virtual void move(double x, double y) = 0;

    virtual void scale(double value) = 0;
  };
}
#endif
