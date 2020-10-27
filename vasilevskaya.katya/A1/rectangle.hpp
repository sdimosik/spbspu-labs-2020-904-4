#ifndef A1_RECTANGLE_H
#define A1_RECTANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const double height, const double width, const point_t& pos);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double onTheAbscissa, const double onTheOrdinate) override;
  void move(const point_t& newPoint) override;
  void printFigure() const override;
private:
  rectangle_t figure_;
};

#endif
