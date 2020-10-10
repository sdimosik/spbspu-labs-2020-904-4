#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const double radius, const point_t& pos);

  rectangle_t getFrameRect() const override;

  double getArea() const override;

  void move(double x, double y) override;

  void move(const point_t& center) override;

  void printData() const override;

  void printFrameRectangle() const override;

  void printArea() const override;
private:
  double radius_;
  point_t pos_;
};

#endif
