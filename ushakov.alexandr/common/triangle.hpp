#ifndef A1_TRIANGLE_HPP
#define A1_TRIANGLE_HPP

#include "shape.hpp"

namespace ushakov
{

  class Triangle : public Shape
  {
  public:
    Triangle(const point_t& top1, const point_t& top2, const point_t& top3);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t& point) override;

    void move(double xAxis, double yAxis) override;

    void print() const override;

    void printFrameRectangle() const override;

    void scale(double coefficient) override;

    point_t getPosition() const;

  private:
    point_t top1_;
    point_t top2_;
    point_t top3_;
    point_t pos_;
  };

}

#endif //A1_TRIANGLE_HPP
