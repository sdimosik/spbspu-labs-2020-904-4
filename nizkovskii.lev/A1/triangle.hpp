#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include <iostream>
#include "shape.hpp"

class Triangle: public Shape
{
public:
  Triangle(const point_t & vertex_1, const point_t & vertex_2, const point_t & vertex_3);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t & point) override;
  void move(const double dx, const double dy) override;
private:
  point_t center_;
  point_t vertices_[3];
  void print(std::ostream & out) const override;
};

#endif
