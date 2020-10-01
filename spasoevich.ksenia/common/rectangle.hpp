#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"

namespace spasoevich
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& center, double width, const double height);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t& p) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
  private:
    rectangle_t rect;
    double angle_;
  };
}

#endif
