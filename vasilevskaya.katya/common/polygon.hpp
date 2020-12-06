#ifndef VASILEVSKAYA_A_POLYGON_HPP
#define VASILEVSKAYA_A_POLYGON_HPP

#include <memory>

#include "shape.hpp"

namespace vasilevskaya
{
  class Polygon : public Shape
  {
  public:
    point_t operator[](size_t index) const;
    Polygon(const std::initializer_list<point_t>& points);
    void move(const point_t& newPoint) override;
    void move(const double onTheAbscissa, const double onTheOrdinate) override;
    void scale(double coefficient) override;
    void rotate(double) override;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    point_t getPosition() const override;
    void printFigure() const override ;
    void printFrameRect() const override;

  private:
    size_t size_;
    std::unique_ptr<point_t[]> points_;
    size_t numberOfPoints_;
    double angle_;
  };
}

#endif 
