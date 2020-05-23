#ifndef CIRCLE_HPP
#define CIRCLE_HPP
#include "shape.hpp"

class Circle : public Shape {
public:
  Circle(const double, const point_t&);
  double getRadius() const;
  point_t getPosition() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const point_t&) override;
  void move (const double, const double) override;
private:
  double radius_;
  point_t pos_;
};

#endif
