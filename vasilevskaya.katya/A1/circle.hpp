#ifndef A1_CIRCLE_H
#define A1_CIRCLE_H

#include "shape.hpp"
#include "base-types.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& point, const double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double onTheAbscissa, const double onTheOrdinate) override;
  void move(const point_t& newPoint) override;
  void printFigure() const override;
private:
  point_t center_;
  double radius_;
};

#endif
