#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double radius, const point_t &point);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(double dx, double dy) override;

  void move(const point_t &point) override;

private:
  double radius_;
  point_t point_;
};
#endif
