#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace bakaeva
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t &pos);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &center) noexcept override;

    void move(double x, double y) noexcept override;

    void printData() const override;

    void printFrameRect() const override;

    void scale(const double coefficient) override;

    void rotate(const double angle) noexcept override;

    point_t getCenter() const noexcept override;

    double getAngle() const noexcept;

  private:
    double width_;
    double height_;
    point_t pos_;
    double angle_;
  };
}

#endif

