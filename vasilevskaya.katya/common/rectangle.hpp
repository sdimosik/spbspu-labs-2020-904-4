#ifndef A1_RECTANGLE_H
#define A1_RECTANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

namespace vasilevskaya
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double height, const double width, const point_t& pos);
    double getArea() const override;
    point_t getPosition() const override;
    double getHeight() const;
    double getWidth() const;
    rectangle_t getFrameRect() const override;
    void move(const double onTheAbscissa, const double onTheOrdinate) override;
    void move(const point_t& newPoint) override;
    void printFigure() const override;
    void printFrameRect() const override;
    void scale(double quotient) override;
  private:
    rectangle_t figure_;
  };
}

#endif
