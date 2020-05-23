#ifndef SHAPE_HPP
#define SHAPE_HPP

#include "base-types.hpp"

class Shape
{
public:

  Shape(point_t pos);

  virtual ~Shape() = default;

  virtual double getArea() const = 0;

  virtual rectangle_t getFrameRect() const = 0;

  virtual void move(double x, double y) = 0;

  virtual void move(const point_t& pos) = 0;

  virtual void printInf() = 0;

  virtual void printFrameInf() = 0;

protected:
  point_t pos_;
};

#endif
