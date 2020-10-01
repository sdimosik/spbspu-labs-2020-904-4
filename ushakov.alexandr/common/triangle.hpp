#ifndef USHAKOV_A_TRIANGLE_HPP
#define USHAKOV_A_TRIANGLE_HPP

#include "shape.hpp"

namespace ushakov
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t& top1, const point_t& top2, const point_t& top3);

    void move(const point_t& newPosition) noexcept override;

    void move(double xAxis, double yAxis) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getPosition() const noexcept override;

    void print() const noexcept override;

    void printFrameRectangle() const noexcept override;

  private:
    point_t tops_[3];
  };
}

#endif //USHAKOV_A_TRIANGLE_HPP
