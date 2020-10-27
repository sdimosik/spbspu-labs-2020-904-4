#ifndef A1_TRIANGLE_H
#define A1_TRIANGLE_H

#include "shape.hpp"
#include "base-types.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t & vertex_1, const point_t & vertex_2, const point_t & vertex_3);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  point_t getPosition() const;
  void move(const point_t & point) override;
  void move(const double dx, const double dy) override;
  void printFigure() const override;
private:
  point_t a_, b_, c_;
  point_t pos_;

};

#endif
