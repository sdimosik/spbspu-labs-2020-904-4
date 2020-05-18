#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(const double, const double, const point_t&);
  double getWidth() const;
  double getHeight() const;
  point_t getPosition() const;
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(const double, const double) override;
  void move(const point_t &) override;

private:
  double width_, height_;
  point_t pos_;
};

#endif
