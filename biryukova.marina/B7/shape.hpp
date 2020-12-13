#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <iosfwd>
#include <memory>
#include "point.hpp"

class Shape
{
public:
  using ShapePtr = std::shared_ptr<Shape>;
  using ConstShapePtr = std::shared_ptr<const Shape>;
  Shape(Point center);
  virtual ~Shape() = default;
  bool isMoreLeft(const Shape& rhs) const;
  bool isUpper(const Shape& rhs) const;
  virtual void draw(std::ostream& out) const = 0;
  Point getCenter() const;
protected:
  Point center_;
};

#endif
