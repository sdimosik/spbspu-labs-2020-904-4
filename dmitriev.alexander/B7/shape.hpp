#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <memory>
#include <iostream>

class Shape
{
public:

  Shape(int, int);

  virtual ~Shape() = default;

  bool isMoreLeft(const Shape &) const;

  bool isUpper(const Shape &) const;

  virtual void draw(std::ostream &) const = 0;

protected:
  int x_;
  int y_;
};

std::ostream &operator<<(std::ostream &, const std::shared_ptr<Shape> &);

std::istream &operator>>(std::istream &, std::shared_ptr<Shape> &);


#endif
