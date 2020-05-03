#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace dmitriev
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &pos, double radius);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &position) override;

    void move(double x, double y) override;

    void scale(double factor) override;

  private:
    point_t pos_;
    double radius_;
  };
}
#endif
