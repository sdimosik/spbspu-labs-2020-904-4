#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double radius, const point_t& dot);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& dot) override;

  void move(double xAxis, double yAxis) override;

private:
  double radius_;
  point_t position_;
};

#endif
