#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "base-types.hpp"
#include "shape.hpp"
class Rectangle: public Shape
{
public:
  Rectangle(rectangle_t contents);
  void print(std::ostream& out) const override;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t& newPosition) override;
  void move(double dx, double dy) override;
private:
  rectangle_t contents_;
};
#endif
