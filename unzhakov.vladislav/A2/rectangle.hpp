#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace unzhakov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &pos);

    rectangle_t getFrameRect() const override;

    double getArea() const override;

    void move(double x, double y) override;

    void move(const point_t &center) override;

    void scale(const double coefficient) override;

    void printData() const override;

    void printFrameRectangle() const override;

    void printArea() const override;

  private:
    double width_;
    double height_;
    point_t pos_;
  };
}
#endif
