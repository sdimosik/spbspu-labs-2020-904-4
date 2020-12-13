#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>

#include "point.hpp"

class Shape
{
public:
  Shape(const Point& point);
  virtual ~Shape() = default;
  bool isMoreLeft(const Shape& shape) const;
  bool isUpper(const Shape& shape) const;
  virtual void draw(std::ostream& out) const = 0;
  using ShapePtr = std::shared_ptr<const Shape>;
protected:
  Point center_;
};

Shape::ShapePtr createShape(const std::string& figureName, const Point& center);
std::ostream& operator <<(std::ostream& out, const Shape::ShapePtr& shape);
std::istream& operator >>(std::istream& in, Shape::ShapePtr& shape);

#endif
