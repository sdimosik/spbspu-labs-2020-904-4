#ifndef POLYGON_HPP
#define POLYGON_HPP

#include <memory>
#include <initializer_list>
#include "shape.hpp"

namespace anastasiev
{
  class Polygon : public Shape
  {
  public:
    Polygon(const std::initializer_list<point_t>&);
    double getArea() const noexcept override;
    rectangle_t getFrameRect() const noexcept override;
    void move(const point_t &) noexcept override;
    void move(const double, const double) noexcept override;
    void scale(const double) override;
    void rotate(double) noexcept override;
    void rotateAroundPoint(double,const point_t&) noexcept override;
    point_t getPosition() noexcept; 
  private:
    bool isConvex() const;
    unsigned int count_;
    std::unique_ptr<point_t[]> points_;
  };
}
#endif
