#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

namespace biryukova
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& centre, double width, double height);
    Rectangle(const rectangle_t& rectangle);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t& centre) noexcept override;
    void move(double x, double y) noexcept override;
    void print() const override;
    void scale(double coefficient) override;
    double getHeight() const noexcept;
    double getWidth() const noexcept;
    point_t getCentre() const noexcept override;
  private:
    rectangle_t rectangle_;
    void testValidParameters(const rectangle_t& rectangle);
  };
}

#endif
