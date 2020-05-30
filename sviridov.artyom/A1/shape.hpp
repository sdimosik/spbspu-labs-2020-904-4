#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iostream>
#include "base-types.hpp"
class Shape
{
public:
  friend std::ostream& operator<<(std::ostream& out, const Shape& out_shape);
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const point_t& pos);
  virtual void move(double dx, double dy);
  virtual ~Shape() = 0;
  virtual void getInform(std::ostream& out) const;
protected:
  point_t pos_;
  Shape(const point_t& pos);
};
std::ostream& operator<<(std::ostream& out, const Shape& out_shape);
#endif
