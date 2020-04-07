#ifndef A1_SHAPE_HPP
#define A1_SHAPE_HPP
#include"base-types.hpp"
#include <iostream>

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(double x, double y) = 0;
  virtual void move(const point_t &spot) = 0;
  virtual void printSpot(std::ostream &out) = 0;
};

#endif //A1_SHAPE_HPP
