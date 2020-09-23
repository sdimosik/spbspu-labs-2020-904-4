#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

namespace vorotnikov {
  class Circle : public Shape {
  public:
    Circle(double radius, const point_t &pos);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &point) override;

    void move(double x, double y) override;

    void scale(double value) override;

    void rotate(double angle) noexcept override;

  private:
    double radius_;
    point_t pos_;
  };
}
#endif
