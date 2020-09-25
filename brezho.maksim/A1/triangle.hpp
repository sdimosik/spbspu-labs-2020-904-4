#ifndef TRIANGLE
#define TRIANGLE

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t& pos, double base, double sideLeft, double sideRight);
  void move(const point_t& pos) override;
  void move(double x, double y) override;
  rectangle_t getFrameRect() const override;
  double getBase() const;
  double getSideLeft() const;
  double getSideRight() const;
  void setBase(double base);
  void setSideLeft(double sideLeft);
  void setSideRight(double sideRight);
  point_t getPosition() const;
  double getArea() const override;
private:
  triangle_t triangle_;
};

#endif
