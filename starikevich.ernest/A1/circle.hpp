#ifndef CIRCLE
#define CIRCLE

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& pos, double radius);
  void move(const point_t& pos) override;
  void move(double x, double y) override;
  rectangle_t getFrameRect() const override;
  double getRadius() const;
  void setRadius(double radius);
  point_t getPosition() const;
  double getArea() const override;
private:
  point_t pos_;
  double radius_;
};

#endif
