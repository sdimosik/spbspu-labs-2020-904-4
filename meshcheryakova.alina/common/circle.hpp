#ifndef A2_CIRCLE_HPP
#define A2_CIRCLE_HPP
#include "shape.hpp"

namespace  meshcheryakova
{
  class Circle : public Shape {
  public:
    Circle(const point_t &pos, double radius);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t &spot) noexcept override;

    void printSpot(std::ostream &out) override;

    void scale(double coefficient) override;

    void printParametersWithoutSpot(std::ostream &out) override;

    void rotate(double angle) noexcept override;

  private:
    point_t pos_;
    double radius_;
  };
}
#endif //A2_CIRCLE_HPP

