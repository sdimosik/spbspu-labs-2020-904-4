#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace maksimova
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double width, const double height, const point_t& pos);

    Rectangle(const rectangle_t& rectangle);

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t& pos) override;

    void move(const double dx, const double dy) override;

    void print() const override;

    void scale(const double coefficient) override;

    double get_width() const;

    double get_height() const;

    void rotate(const double angle) override;

    double getAngle() const;

  private:
    double width_;
    double height_;
    point_t position_;
    double angle_;
  };
}

#endif
