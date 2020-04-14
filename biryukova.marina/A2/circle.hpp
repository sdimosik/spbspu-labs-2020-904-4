#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "base-types.hpp"
#include "shape.hpp"

namespace biryukova
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& point, double radius);
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void move(const biryukova::point_t& point) override;
    void move(double x, double y) override;
    void print() const override;
    void scale(double coefficient) override;
    double getRadius() const;
    point_t getPosition() const;
  private:
    double radius_;
    point_t centre_;
  };
}

#endif
