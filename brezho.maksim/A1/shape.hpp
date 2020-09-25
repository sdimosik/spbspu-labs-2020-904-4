#ifndef SHAPE
#define SHAPE
#include"base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const double x, const double y) = 0;
  virtual void move(const point_t& point) = 0;
};

#endif
