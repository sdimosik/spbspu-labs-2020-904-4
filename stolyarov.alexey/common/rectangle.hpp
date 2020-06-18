#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace stolyarov
{
  class Rectangle : public Shape
  {
  public:

    Rectangle(double width, double height, const point_t& pos);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getCenter() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t& pos) noexcept override;

    void printInf() override;

    void printFrameInf() override;

    void scale(const double rate) override;

    void rotate(const double angle) noexcept override;

    double getAngle() const noexcept;

  private:
    double width_;
    double height_;
    double angle_;
  };
}

#endif
