#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace bulanov
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t &center);

    void move(double x, double y) noexcept override;

    void move(const point_t &center) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getCenter() const noexcept override;

    void printInform() const override;

    void printFrameInform() const override;

    void scale(const double rate) override;

  private:
    double radius_;
    point_t pos_;
  };
}

#endif

