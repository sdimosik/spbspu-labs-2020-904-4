#include <iostream>
#include "circle.hpp"
#include "rectangle.hpp"
#include "triangle.hpp"
#include "composite-shape.hpp"

int main()
{
  auto rectangle = std::make_shared<sviridov::Rectangle>(sviridov::point_t{2, 3}, 5, 4);
  sviridov::CompositeShape compositeShape(rectangle);
  return 0;
};
