#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace unzhakov
{
  class Rectangle: public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& centre, double angle = 0);

    rectangle_t getFrameRect() const override;

    double getArea() const override;

    point_t getCenter() const override;

    double getWidth() const;

    double getHeight() const;

    void move(double x, double y) override;

    void move(const point_t &center) override;

    void scale(const double coefficient) override;

    void rotate(double angle) override;

    void printData() const override;

    void printFrameRectangle() const override;

    void printArea() const override;

  private:
    point_t vertex_[4];
  };
}
#endif
