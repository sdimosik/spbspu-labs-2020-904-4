#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace bakaeva
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t &pos);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &center) noexcept override;

    void move(double x, double y) noexcept override;

    void printData() const override;

    void printFrameRect() const override;

    void scale(const double coefficient) override;

    void rotate(const double angle) noexcept override;

    point_t getCenter() const noexcept override;

  private:
    double radius_;
    point_t pos_;
  };
}

#endif

