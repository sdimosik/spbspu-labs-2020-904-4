#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace bakaeva
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t &pos);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &center) override;

    void move(double x, double y) override;

    void printData() const override;

    void printFrameRect() const override;

    void scale(const double coefficient) override;

  private:
    double radius_;
    point_t pos_;
  };
}

#endif

