#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <memory>
#include "shape.hpp"

namespace unzhakov
{
  class Polygon: public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t> &pts);

    point_t operator[](std::size_t index) const;

    void move(double dx, double dy) override;

    void move(const point_t &centre) override;

    void scale(double coefficient) override;

    void rotate(double angle) override;

    double getArea() const override;

    rectangle_t getFrameRect() const override;

    point_t getCenter() const override;

    void printData() const override;

    void printFrameRectangle() const override;

    void printArea() const override;

  private:
    std::size_t size_;
    std::unique_ptr<point_t[]> points_;
  };
}

#endif
