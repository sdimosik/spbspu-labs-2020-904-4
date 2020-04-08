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
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& centre) override;
    void move(double x, double y) override;
    void print() const override;
    void scale(double coefficient) override;
    double getHeight() const;
    double getWidth() const;
    point_t getPosition() const;
  private:
    rectangle_t rectangle_;
    void testValidParameters(const rectangle_t& rectangle);
  };
}

#endif
