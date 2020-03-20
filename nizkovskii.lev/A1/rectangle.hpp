#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <iostream>
#include "shape.hpp"

class Rectangle: public Shape
{
public:
  Rectangle(const point_t & pos, const double width, const double height);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & point) override;
  void move(const double dx, const double dy) override;
private:
  point_t pos_;
  double width_;
  double height_;
  void print(std::ostream & out) const override;
};

#endif
