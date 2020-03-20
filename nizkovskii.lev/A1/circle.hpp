#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include <iostream>
#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t & pos, const double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & point) override;
  void move(const double dx, const double dy) override;
private:
  point_t pos_;
  double radius_;
  void print(std::ostream & out) const override;
};

#endif
