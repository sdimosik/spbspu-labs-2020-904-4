#ifndef CIRCLE_HPP
#define CIRCLE_HPP


#include "shape.hpp"

namespace khilchenko
{
  class Circle :public Shape
  {
  public:
    Circle(double rad, const point_t &pos);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const override;
    void move(const point_t &newPos) noexcept override;
    void move(double x, double y) noexcept override;
    point_t getCenter() const noexcept override;
    void scale(double coefficient) override;
  private:
    double rad_;
    point_t pos_;
  };
}
#endif
