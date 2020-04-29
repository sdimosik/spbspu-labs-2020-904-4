#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
namespace bulanov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &center, double width, double height);

    void move(double x, double y) override;

    void move(const point_t &center) override;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    point_t getCenter() const override;

    void printInform() const override;

    void printFrameInform() const override;

    void scale(const double rate) override;

  private:
    double width_, height_;
    point_t pos_;
  };
}

#endif

