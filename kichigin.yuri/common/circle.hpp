#ifndef CIRCLE
#define CIRCLE

#include "shape.hpp"

namespace kichigin
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t& position);
    double getRadius() const noexcept;
    point_t getPosition() const noexcept;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void setRadius(double radius);
    void move(const point_t& position) noexcept override;
    void move(double x, double y) noexcept override;
    void scale(double coefficient) override;
    void rotate(double angle) noexcept override;
  private:
    double radius_;
    point_t pos_;
  };
}

#endif // !CIRCLE
