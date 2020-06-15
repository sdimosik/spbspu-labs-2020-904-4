#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

namespace stolyarov
{
  class Shape
  {
  public:

    Shape() noexcept;

    Shape(const point_t& pos) noexcept;

    virtual ~Shape() = default;

    virtual double getArea() const noexcept = 0;

    virtual rectangle_t getFrameRect() const noexcept = 0;

    virtual point_t getCenter() const noexcept = 0;

    virtual void move(double x, double y) noexcept = 0;

    virtual void move(const point_t& pos) noexcept = 0;

    virtual void printInf() = 0;

    virtual void printFrameInf() = 0;

    virtual void scale(const double rate) = 0;

  protected:
    point_t pos_;
  };
}

#endif
