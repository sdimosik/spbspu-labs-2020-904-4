#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace biryukova
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& point, double radius);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const biryukova::point_t& point) noexcept override;
    void move(double x, double y) noexcept override;
    void print() const override;
    void scale(double coefficient) override;
    double getRadius() const noexcept;
    point_t getCentre() const noexcept override;
  private:
    double radius_;
    point_t centre_;
  };
}

#endif
