
#ifndef shape_h
#define shape_h
#include <iostream>
#include "base-types.hpp"
namespace rodion
{
  class Shape {
  public:
      virtual ~Shape() = default;

      virtual double getArea() const = 0;

      virtual rectangle_t getFrameRect() const = 0;

      virtual void move(const point_t &point) = 0;

      virtual void move(const double x, const double y) = 0;

      virtual void show() const = 0;

      virtual void scale (double value) = 0;
    
      virtual void rotate(double angle) noexcept = 0;
  };
};
#endif /* shape_h */
