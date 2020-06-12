#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP
#include "shape.hpp"
class Rectangle :public Shape
{
public:
  double getArea() const;
  rectangle_t getFrameRect() const;
  Rectangle(const point_t& pos, double height, double width);
  friend std::ostream& operator<<(std::ostream& out, const Rectangle& out_rect);
private:
  double height_;
  double width_;
  void getInform(std::ostream& out) const;
};
std::ostream& operator<<(std::ostream& out, const Rectangle& out_rect);
#endif
