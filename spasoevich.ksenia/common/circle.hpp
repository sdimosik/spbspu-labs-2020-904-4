#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace spasoevich
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& center, double radius);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const double dx, const double dy) noexcept override;
    void move(const point_t& pt) noexcept override;
    void scale(const double coefficient) override;
    void rotate(const double angle) noexcept override;
  private:
    point_t center_;
    double radius_;
  };
}

#endif
