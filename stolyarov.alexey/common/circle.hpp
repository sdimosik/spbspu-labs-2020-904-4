#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace stolyarov
{
  class Circle : public Shape
  {
  public:

    Circle(double radius, const point_t& pos);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getCenter() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t& pos) noexcept override;

    void printInf() override;

    void printFrameInf() override;

    void scale(const double rate) override;

  private:
    double radius_;
  };
}

#endif
