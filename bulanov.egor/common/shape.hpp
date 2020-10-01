#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"
namespace bulanov
{
  class Shape
  {
  public:
    virtual ~Shape() = default;

    virtual double getArea() const noexcept = 0;

    virtual rectangle_t getFrameRect() const noexcept = 0;

    virtual void move(double x, double y) noexcept = 0;

    virtual void move(const point_t &center) noexcept = 0;

    virtual point_t getCenter() const noexcept = 0;

    virtual void printInform() const = 0;

    virtual void printFrameInform() const = 0;

    virtual void scale(const double rate) = 0;

    virtual void rotate(const double angle) noexcept = 0;

  };
}

#endif
