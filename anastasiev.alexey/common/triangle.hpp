#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

namespace anastasiev
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t &, const point_t &, const point_t &);
    point_t getPosition() const;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &) noexcept override;
    void move(const double, const double) noexcept override;
    void scale(const double) override;
  private:
    point_t a_, b_, c_, pos_;
  };
}//namespace anastasiev
#endif
