#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& centre, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& centre) override;
  void move(double x, double y) override;
  void print() const override;
private:
  double radius_;
  point_t centre_;
};

#endif
