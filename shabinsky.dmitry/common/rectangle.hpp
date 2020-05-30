#ifndef HW01_RECTANGLE_H
#define HW01_RECTANGLE_H
#include "shape.hpp"

namespace shabinsky
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const point_t &position, double width, double height);

    double getWidth() const;

    double getHeight() const;

    point_t getPosition() const;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    void move(const point_t &position) override;

    void move(double x, double y) override;

    void show(std::ostream &out) override;

    void scale(double coefficient);

  private:
    double width_, height_;
    point_t position_;
  };
}

#endif //HW01_RECTANGLE_H
