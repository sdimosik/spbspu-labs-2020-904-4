#ifndef CIRCLE
#define CIRCLE
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(double radius, const point_t &pos);

  double getArea() const override;

  void move(const point_t &pos) override;

  void move(double dx, double dy) override;

  rectangle_t getFrameRect() const override;

  void print();

private:
  double radius_;
  point_t center_;
};

#endif
