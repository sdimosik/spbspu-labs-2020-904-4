#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace dmitriev
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t &pos, double radius);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &position) noexcept override;

    void move(double x, double y) noexcept override;

    void scale(double factor) override;

    void rotate(double angle) noexcept override;

  private:
    point_t pos_;
    double radius_;
  };
}
#endif
