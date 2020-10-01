#ifndef USHAKOV_A_CIRCLE_HPP
#define USHAKOV_A_CIRCLE_HPP

#include "shape.hpp"

namespace ushakov
{

  class Circle : public Shape
  {
  public:
    Circle(const point_t& position, double radius);

    void move(const point_t& newPosition) noexcept override;

    void move(double xAxis, double yAxis) noexcept override;

    void scale(double coefficient) override;

    void rotate(double) noexcept override
    {};

    double getRadius() const noexcept;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getPosition() const noexcept override;

    void print() const noexcept override;

    void printFrameRectangle() const noexcept override;

  private:

    point_t position_;

    double radius_;
  };

}

#endif //USHAKOV_A_CIRCLE_HPP
