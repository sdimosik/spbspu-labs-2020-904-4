#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace lovkacheva
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t& contents);

    void print(std::ostream& out) const override;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t& newPosition) override;

    void move(double dx, double dy) override;

    void scale(double coefficient) override;

  private:
    rectangle_t contents_;
  };
}
#endif
