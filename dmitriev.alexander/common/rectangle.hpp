#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace dmitriev
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &pos, double width, double height);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(const point_t &position) noexcept override;

    void move(double x, double y) noexcept override;

    void scale(double factor) override;

    void rotate(double angle) noexcept override;

  private:
    point_t pos_;
    double width_;
    double height_;
    double angle_;
  };
}
#endif
