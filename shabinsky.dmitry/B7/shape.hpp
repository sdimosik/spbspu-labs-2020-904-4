#ifndef B7_SHAPE_HPP
#define B7_SHAPE_HPP

#include <memory>
#include <iostream>

class Shape
{
public:
  using ShapePtr = std::shared_ptr<Shape>;
  
  Shape(int, int);
  
  virtual ~Shape() = default;
  
  bool isMoreLeft(const Shape &) const;
  
  bool isUpper(const Shape &) const;
  
  virtual void draw(std::ostream &) const = 0;

protected:
  int x_;
  int y_;
};

std::ostream &operator<<(std::ostream &, const Shape::ShapePtr &);

std::istream &operator>>(std::istream &, Shape::ShapePtr &);

#endif
