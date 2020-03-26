#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double radius, const point_t &center);

  void move(double x, double y) override;

  void move(const point_t &center) override;

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  point_t getCenter() const override;

  void printInform() const override;

  void printFrameInform() const override;

private:
  double radius_;
  point_t pos_;
};


#endif

