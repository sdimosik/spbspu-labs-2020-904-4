#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP

#include <iostream>
#include "base-types.hpp"

class Shape
{
public:

  virtual ~Shape() = default;

  virtual double getArea() const = 0;

  virtual rectangle_t getFrameRect() const = 0;

  virtual void move(const point_t& point) = 0;

  virtual void move(double xAxis, double yAxis) = 0;

  virtual void print() const = 0;

  virtual void printFrameRectangle() const = 0;
};

#endif //A1_SHAPE_HPP
