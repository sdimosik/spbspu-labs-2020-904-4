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

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t& newPosition) noexcept override;

    void move(double dx, double dy) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) noexcept override ;

  private:
    rectangle_t contents_;
    double angle_;
  };
}
#endif
