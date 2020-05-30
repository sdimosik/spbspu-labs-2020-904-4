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

    double getArea() const  override;

    rectangle_t getFrameRect() const override;

    void move(double x, double y) override;

    void move(const point_t& pos) override;

    void printInf() override;

    void printFrameInf() override;

    void scale(const double rate) override;

  private:
    double radius_;
  };
}

#endif
