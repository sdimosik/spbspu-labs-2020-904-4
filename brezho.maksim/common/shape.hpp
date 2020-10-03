#ifndef SHAPE
#define SHAPE
#include"base-types.hpp"

namespace brezho
{
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const noexcept = 0;
    virtual point_t getPosition() const noexcept = 0;
    virtual rectangle_t getFrameRect() const noexcept = 0;
    virtual void move(const double x, const double y) noexcept = 0;
    virtual void move(const point_t& point) noexcept = 0;
    virtual void scale(double coefficient) = 0;
    virtual void rotate(double angle) noexcept = 0;
  };
}

#endif
