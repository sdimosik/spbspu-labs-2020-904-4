#ifndef GEOMETRIC_FIGURES_HPP
#define GEOMETRIC_FIGURES_HPP

#include "shape.hpp"

class Circle : public Shape
{
public:
  using Shape::Shape;
  void draw(std::ostream& out) const override;
};

class Triangle : public Shape
{
public:
  using Shape::Shape;
  void draw(std::ostream& out) const override;
};

class Square : public Shape
{
public:
  using Shape::Shape;
  void draw(std::ostream& out) const override;
};

#endif

