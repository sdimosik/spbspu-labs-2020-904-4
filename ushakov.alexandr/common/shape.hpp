#ifndef USHAKOV_A_SHAPE_HPP
#define USHAKOV_A_SHAPE_HPP

#include "base-types.hpp"

namespace ushakov
{

  class Shape
  {
  public:

    virtual ~Shape() = default;

    virtual void move(const point_t&) noexcept = 0;

    virtual void move(double, double) noexcept = 0;

    virtual void scale(double) = 0;

    virtual void rotate(double) noexcept = 0;

    virtual double getArea() const noexcept = 0;

    virtual rectangle_t getFrameRect() const noexcept = 0;

    virtual point_t getPosition() const noexcept = 0;

    virtual void print() const noexcept = 0;

    virtual void printFrameRectangle() const noexcept = 0;
  };
}

#endif //USHAKOV_A_SHAPE_HPP
