#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
namespace bulanov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &center, double width, double height);

    void move(double x, double y) noexcept override;

    void move(const point_t &center) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getCenter() const noexcept override;

    void printInform() const override;

    void printFrameInform() const override;

    void scale(const double rate) override;

    void rotate(const double angle) noexcept override;

    double getAngle() const noexcept;

  private:
    double width_, height_;
    point_t pos_;
    double angle_;
  };
}

#endif

