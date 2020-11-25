#ifndef TRIANGLE
#define TRIANGLE

#include "shape.hpp"

namespace starikevich
{
  class Triangle : public Shape
  {
  public:
    Triangle(const point_t& peak1, const point_t& peak2, const point_t& peak3);
    void move(const point_t& pos) noexcept override;
    void move(double x, double y) noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    double getSide1() const noexcept;
    double getSide2() const noexcept;
    double getSide3() const noexcept;
    point_t getPosition() const noexcept override;
    double getArea() const noexcept override;
    void scale(double coefficient) override;
    void rotate(double angle) noexcept override;
  private:
    point_t peaks_[3];
  };
}

#endif
