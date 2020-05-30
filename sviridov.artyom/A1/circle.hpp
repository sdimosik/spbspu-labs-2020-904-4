#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"
class Circle : public Shape
{
public:
  double getArea() const;
  rectangle_t getFrameRect() const;
  Circle(const point_t& pos, double rad);
  friend std::ostream& operator<<(std::ostream& out, const Circle& out_cir);
private:
  double rad_;
  void getInform(std::ostream& out) const;
};
std::ostream& operator<<(std::ostream& out, const Circle& out_cir);
#endif
