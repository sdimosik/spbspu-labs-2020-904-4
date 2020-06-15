#ifndef SHAPE_HPP
#define SHAPE_HPP
#include "base-types.hpp"

namespace biryukova
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual biryukova::rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const biryukova::point_t& point) noexcept = 0;
    virtual void move(double x, double y) noexcept = 0;
    virtual void print() const = 0;
    virtual void scale(double coefficient) = 0;
    virtual point_t getCentre() const noexcept = 0;
    virtual void rotate(double angle) = 0;
  };
}

#endif
