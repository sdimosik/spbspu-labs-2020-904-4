#ifndef CIRCLE_H
#define CIRCLE_H
#include "shape.h"

namespace vorotnikov {
  class Circle : public Shape {
  public:
    Circle(double radius, const point_t &pos);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &point) override;

    void move(double x, double y) override;

    void scale(double value) override;

  private:
    double radius_;
    point_t pos_;
  };
}
#endif
