#ifndef CIRCLE_HPP
#define CIRCLE_HPP


#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double rad, const point_t& pos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newPos) override;
  void move(double x, double y) override;
  point_t getCenter() const override;
private:
  double rad_;
  point_t pos_;
};

#endif
