#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP
#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t &spot);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(double x, double y) override;
  void move(const point_t &spot) override;
  void printSpot(std::ostream &out) override;
private:
  double width_;
  double height_;
  point_t pos_;
};

#endif //A1_RECTANGLE_HPP
