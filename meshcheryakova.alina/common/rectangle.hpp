#ifndef A2_RECTANGLE_HPP
#define A2_RECTANGLE_HPP
#include "shape.hpp"

namespace  meshcheryakova
{
  class Rectangle : public Shape {
  public:
    Rectangle(double width, double height, const point_t &spot);

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    void move(double x, double y) noexcept override;

    void move(const point_t &spot) noexcept override;

    void printSpot(std::ostream &out) override;

    void scale(double coefficient) override;

    void printParametersWithoutSpot(std::ostream &out) override;

    void rotate(double angle) noexcept override;

  private:
    double width_;
    double height_;
    point_t pos_;
    double angle_;
  };
}
#endif //A2_RECTANGLE_HPP

