#ifndef TRIANGLE
#define TRIANGLE

#include "shape.hpp"

class Triangle : public Shape
{
public:
  Triangle(const point_t& peak1, const point_t& peak2, const point_t& peak3);
  void move(const point_t& pos) override;
  void move(double x, double y) override;
  rectangle_t getFrameRect() const override;
  double getSide1() const;
  double getSide2() const;
  double getSide3() const;
  point_t getPosition() const;
  double getArea() const override;
private:
  point_t peaks_[3];
};

#endif
