#ifndef USHAKOV_A_RECTANGLE_HPP
#define USHAKOV_A_RECTANGLE_HPP

#include "shape.hpp"

namespace ushakov
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(double width, double height, const point_t& position);

    void move(const point_t& newPosition) noexcept override;

    void move(double xAxis, double yAxis) noexcept override;

    void scale(double coefficient) override;

    void rotate(double angle) noexcept override;

    double getWidth() const noexcept;

    double getHeight() const noexcept;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getPosition() const noexcept override;

    void print() const noexcept override;

    void printFrameRectangle() const noexcept override;

  private:
    point_t tops_[4];
  };

}

#endif //USHAKOV_A_RECTANGLE_HPP
