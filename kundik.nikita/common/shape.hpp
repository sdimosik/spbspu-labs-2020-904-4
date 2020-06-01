#ifndef shape_hpp
#define shape_hpp

#include "base-types.hpp"

namespace kundik {
  class Shape
  {
  public:
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const point_t& endPos) = 0;
    virtual void move(double changeX, double changeY) = 0;
    virtual void scale(double coefficent) = 0;
  };
}
#endif
