#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

namespace maksimova
{
  class Circle : public Shape
  {
  public:
    Circle(const double radius, const point_t &pos);

    double getArea() const override;

    void move(const point_t &pos) override;

    void move(const double dx, const double dy) override;

    rectangle_t getFrameRect() const override;

    void print() const override;

    double getRadius() const;

    point_t getCenter() const;

    void scale(const double coefficient) override;

  private:
    double radius_;
    point_t center_;
  };
}

#endif
