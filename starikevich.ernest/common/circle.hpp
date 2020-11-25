#ifndef CIRCLE
#define CIRCLE

#include "shape.hpp"

namespace starikevich
{
  class Circle : public Shape
  {
  public:
    Circle(const point_t& pos, double radius);
    void move(const point_t& pos) noexcept override;
    void move(double x, double y) noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    double getRadius() const noexcept;
    void setRadius(double radius);
    point_t getPosition() const noexcept override;
    double getArea() const noexcept override;
    void rotate(double) noexcept override;
    void scale(double coefficient) override;
  private:
    point_t pos_;
    double radius_;
  };
}

#endif
