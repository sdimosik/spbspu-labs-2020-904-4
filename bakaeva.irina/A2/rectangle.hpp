#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace bakaeva
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &pos);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &center) override;

    void move(double x, double y) override;

    void printData() const override;

    void printFrameRect() const override;

    void scale(const double coefficient) override;

  private:
    double width_;
    double height_;
    point_t pos_;
  };
}

#endif

