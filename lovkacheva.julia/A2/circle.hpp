#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace lovkacheva
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t& centre);

    void print(std::ostream& out) const override;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t& newPosition) override;

    void move(double dx, double dy) override;

    void scale(double coefficient) override;

  private:
    double radius_;
    point_t centre_;
  };
}
#endif
