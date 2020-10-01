#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

namespace anastasiev
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(const double, const double, const point_t&);
    double getWidth() const;
    double getHeight() const;
    point_t getPosition() const;
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const double, const double) noexcept override;
    void move(const point_t &) noexcept override;
    void scale(const double) override;
    void rotate (double) noexcept override;
    void rotateAroundPoint (double, const point_t&) noexcept override;
  private:
    point_t corners_[4];
  };
}//namespace anastasiev
#endif
