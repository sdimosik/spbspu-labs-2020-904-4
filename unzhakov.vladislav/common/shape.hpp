#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"
#include <memory>

namespace unzhakov
{
  class Shape
  {
  public:
    using SharedPtr = std::shared_ptr<Shape>;

    virtual ~Shape() = default;

    virtual rectangle_t getFrameRect() const = 0;

    virtual double getArea() const = 0;

    virtual point_t getCenter() const = 0;

    virtual void move(double x, double y) = 0;

    virtual void move(const point_t &center) = 0;

    virtual void scale(const double coefficient) = 0;

    virtual void rotate(double angle) = 0;

    virtual void printData() const = 0;

    virtual void printFrameRectangle() const = 0;

    virtual void printArea() const = 0;
  };
}
#endif
