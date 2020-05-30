#ifndef TRIANGLE_HPP
#define TRIANGLE_HPP
#include "shape.hpp"
class Triangle : public Shape
{
public:
  double getArea() const;
  rectangle_t getFrameRect() const;
  Triangle(const point_t& a,const point_t& b,const point_t& c);
  friend std::ostream& operator<<(std::ostream& out, const Triangle& out_tri);
  void move(const point_t& end_pos);
  void move(double dx, double dy);
private:
  point_t a_;
  point_t b_;
  point_t c_;
  void getInform(std::ostream& out) const;
};
std::ostream& operator<<(std::ostream& out, const Triangle& out_tri);
#endif
