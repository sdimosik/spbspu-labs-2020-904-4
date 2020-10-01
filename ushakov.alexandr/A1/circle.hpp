#ifndef A1_CIRCLE_HPP
#define A1_CIRCLE_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  Circle(const point_t& center, double radius);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& point) override;

  void move(double xAxis, double yAxis) override;

  point_t getPos() const;

  double getRadius() const;

  void print() const override;

  void printFrameRectangle() const override;

private:

  point_t pos_;

  double radius_;
};

#endif //A1_CIRCLE_HPP
