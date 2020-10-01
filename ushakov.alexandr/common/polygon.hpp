#ifndef USHAKOV_A_POLYGON_HPP
#define USHAKOV_A_POLYGON_HPP

#include <memory>

#include "shape.hpp"

namespace ushakov
{
  class Polygon : public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t>& points);

    void move(const point_t& newPosition) noexcept override;

    void move(double xAxis, double yAxis) noexcept override;

    void scale(double coefficient) override;

    void rotate(double) noexcept override;

    double getArea() const noexcept override;

    rectangle_t getFrameRect() const noexcept override;

    point_t getPosition() const noexcept override;

    void print() const noexcept override ;

    void printFrameRectangle() const noexcept override;

  private:
    bool isConvex() const;

    size_t numberOfPoints_;

    std::unique_ptr<point_t[]> points_;
  };
}

#endif //USHAKOV_A_POLYGON_HPP
