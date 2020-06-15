#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace khilchenko
{
  class Rectangle :public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &pos);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newPos) noexcept override;
    void move(double x, double y) noexcept override;
    point_t getCenter() const noexcept override;
    void scale(double coefficient) override;
    void rotate(double angle) noexcept override;
  private:
    double angle_;
    rectangle_t figure_;
  };
}
#endif
