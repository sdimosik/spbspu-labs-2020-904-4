#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace meshcheryakov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const rectangle_t &rect);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(double dx, double dy) override;
    void move(const point_t &point) override;
    void scale(const double coefficient) override;
    point_t getPosition() const noexcept override;
    double getWidth() const;
    double getHeight() const;

  private:
    rectangle_t rect_;
  };
}
#endif
