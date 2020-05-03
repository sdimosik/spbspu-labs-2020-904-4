#ifndef CIRCLE
#define CIRCLE

#include "shape.hpp"

namespace kichigin
{
  class Circle : public Shape
  {
  public:
    Circle(double radius, const point_t& position);
    double getRadius() const;
    point_t getPosition() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    void setRadius(double radius);
    void move(const point_t& position) override;
    void move(double x, double y) override;
    void scale(double coefficient) override;
  private:
    double radius_;
    point_t pos_;
  };
}

#endif // !CIRCLE
