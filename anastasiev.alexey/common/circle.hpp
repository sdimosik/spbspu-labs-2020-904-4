#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace anastasiev
{
  class Circle : public Shape {
  public:
    Circle(const double, const point_t&);
    double getRadius() const;
    point_t getPosition() const;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t&) noexcept override;
    void move (const double, const double) noexcept override;
    void scale(const double) override;
  private:
    double radius_;
    point_t pos_;
  };
}//namespace anastasiev
#endif
