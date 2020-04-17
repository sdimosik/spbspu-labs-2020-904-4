#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace khilchenko
{
  class Rectangle :public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &pos);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newPos) override;
    void move(double x, double y) override;
    point_t getCenter() const override;
    void scale(double coefficient) override;
  private:
    rectangle_t figure_;
  };
}
#endif
