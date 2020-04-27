#ifndef RECTANGLE
#define RECTANGLE

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t& pos);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& pos) override;

  void move(double dx, double dy) override;

  void print();

private:
  double width_;
  double height_;
  point_t position_;
};

#endif
