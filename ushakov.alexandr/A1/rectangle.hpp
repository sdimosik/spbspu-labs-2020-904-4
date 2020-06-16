#ifndef A1_RECTANGLE_HPP
#define A1_RECTANGLE_HPP

#include "shape.hpp"

class Rectangle : public Shape
{
public:
  Rectangle(double width, double height, const point_t& pos);

  explicit Rectangle(const rectangle_t& rectangle);

  double getArea() const override;

  rectangle_t getFrameRect() const override;

  void move(const point_t& point) override;

  void move(double xAxis, double yAxis) override;

  point_t getPosition() const;

  double getWidth() const;

  double getHeight() const;

  void print() const override;

  void printFrameRectangle() const override;

private:
  double width_;
  double height_;
  point_t pos_;
};

#endif //A1_RECTANGLE_HPP
