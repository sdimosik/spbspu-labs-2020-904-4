#ifndef HW01_CIRCLE_H
#define HW01_CIRCLE_H
#include "shape.hpp"

namespace shabinsky
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t &position);

    double getRadius() const;

    point_t getPosition() const;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &position) override;

    void move(double x, double y) override;

    void show(std::ostream &out) override;

    void scale(double coefficient) override;

  private:
    double radius_;
    point_t position_;
  };
}
#endif //HW01_CIRCLE_H
