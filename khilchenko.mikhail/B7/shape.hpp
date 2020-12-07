#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <memory>

#include "point.hpp"

class Shape
{
public:
  Shape(const Point&);
  virtual ~Shape() = default;
  bool isMoreLeft(const Shape&) const noexcept;
  bool isUpper(const Shape&) const noexcept;
  virtual void draw(std::ostream&) const = 0;
protected:
  Point center;
};

#endif
