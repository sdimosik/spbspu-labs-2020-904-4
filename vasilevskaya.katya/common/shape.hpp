#ifndef SHAPE_H
#define SHAPE_H

#include <memory>

namespace vasilevskaya
{
  struct rectangle_t;
  struct point_t;

  class Shape
  {
  public:
    using PointToShape = std::shared_ptr<vasilevskaya::Shape>;
    virtual ~Shape() = default;
    virtual double getArea() const = 0;
    virtual point_t getPosition() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual void move(const double onTheAbscissa, const double onTheOrdinate) = 0;
    virtual void move(const point_t& newPoint) = 0;
    virtual void printFigure() const = 0;
    virtual void scale(double quotient) = 0;
    virtual void printFrameRect() const = 0;
  };
}

#endif
