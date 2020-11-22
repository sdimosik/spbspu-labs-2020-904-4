#ifndef A1_TRIANGLE_H
#define A1_TRIANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

namespace vasilevskaya
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t& a_, const point_t& b_, const point_t& c_);
    double getArea() const override;
    point_t getPosition() const override;
    rectangle_t getFrameRect() const override;
    void move(const point_t& point) override;
    void move(const double dx, const double dy) override;
    void printFigure() const override;
    void printFrameRect() const override;
    void scale(double quotient) override;
  private:
    point_t a_, b_, c_;
    point_t pos_;

  };
}

#endif
