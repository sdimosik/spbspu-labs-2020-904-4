#ifndef SHAPE_H
#define SHAPE_H

struct rectangle_t;
struct point_t;

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(const double onTheAbscissa, const double onTheOrdinate) = 0;
  virtual void move(const point_t& newPoint) = 0;
  virtual void printFigure() const = 0;
};


#endif
