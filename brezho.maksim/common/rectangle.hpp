#ifndef RECTANGLE
#define RECTANGLE

#include "shape.hpp"

namespace brezho
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t& pos, double width, double height);
    void move(const point_t& pos) noexcept override;
    void move(double x, double y) noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    double getWidth() const noexcept;
    double getHeight() const noexcept;
    point_t getPosition() const noexcept override;
    double getArea() const noexcept override;
    void scale(double coefficient) override;
  private:
    point_t peaks_[4];
  };
}

#endif
