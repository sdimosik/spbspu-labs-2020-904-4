#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace spasoevich
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& center, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const double dx, const double dy) override;
    void move(const point_t& pt) override;
    void scale(const double coefficient) override;
  private:
    point_t center_;
    double radius_;
  };
}

#endif
