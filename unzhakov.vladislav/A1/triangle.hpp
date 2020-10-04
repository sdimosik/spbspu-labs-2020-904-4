#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t& vertex1, const point_t& vertex2, const point_t& vertex3);

  rectangle_t getFrameRect() const override;

  double getArea() const override;

  void move(const double x, const double y) override;

  void move(const point_t& center) override;

  void printData() const override;

  void printFrameRectangle() const override;

  void printArea() const override;
private:
  point_t vertex1_, vertex2_, vertex3_;

  void changVertexVal(const point_t& pos);
};

#endif
