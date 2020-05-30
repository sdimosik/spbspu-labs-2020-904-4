#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

namespace vorotnikov {
  class Triangle : public Shape {
  public:
    Triangle(const point_t &point_one, const point_t &point_two, const point_t &point_three);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &point) override;

    void move(double x, double y) override;

    double getCenterX() const;

    double getCenterY() const;

    void scale(double value) override;

  private:
    point_t point_one_, point_two_, point_three_;
    point_t pos_;
  };
}
#endif
