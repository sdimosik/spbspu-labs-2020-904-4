#ifndef A1_CIRCLE_H
#define A1_CIRCLE_H

#include "shape.hpp"
#include "base-types.hpp"
namespace vasilevskaya
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& point, const double radius);
    double getArea() const override;
    point_t getPosition() const override;
    double getRadius() const;
    rectangle_t getFrameRect() const override;
    void move(const double onTheAbscissa, const double onTheOrdinate) override;
    void move(const point_t& newPoint) override;
    void printFigure() const override;
    void printFrameRect() const override;
    void scale(double quotient) override;
  private:
    point_t center_;
    double radius_;
  };
}

#endif
