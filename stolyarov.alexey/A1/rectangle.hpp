#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "base-types.hpp"
#include "shape.hpp"

class Rectangle : public Shape
{
public:

  Rectangle(double width, double height, const point_t& pos);

  double getArea() const override;

  rectangle_t getFrameRect() const;

  void move(double x, double y) override;

  void move(const point_t& pos) override;

  void printInf() override;

  void printFrameInf() override;

private:
  double width_;
  double height_;
};

#endif
