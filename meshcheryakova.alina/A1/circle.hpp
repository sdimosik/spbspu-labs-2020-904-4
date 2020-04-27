#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP
#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t &pos, double radius);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double x, double y) override;
  void move(const point_t &spot) override;
  void printSpot(std::ostream &out) override;
private:
  point_t pos_;
  double radius_;
};

#endif //A1_CIRCLE_HPP
