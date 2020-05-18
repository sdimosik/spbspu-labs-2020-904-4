#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t &, const point_t &, const point_t &);
  point_t getPosition() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t &) override;
  void move(const double, const double) override;
private:
  point_t a_, b_, c_, pos_;
};

#endif
