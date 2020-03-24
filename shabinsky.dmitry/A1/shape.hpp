#ifndef HW01_SHAPE_H
#define HW01_SHAPE_H
#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  
  virtual double getArea() const = 0;
  
  virtual rectangle_t getFrameRect() const = 0;
  
  virtual void move(const point_t &point) = 0;
  
  virtual void move(double x, double y) = 0;
};

#endif //HW01_SHAPE_H
