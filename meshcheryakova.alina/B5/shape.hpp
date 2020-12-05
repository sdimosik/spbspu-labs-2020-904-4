#ifndef B5_SHAPE_HPP
#define B5_SHAPE_HPP

#include <vector>
#include <iostream>

struct Point
{
  int x, y;
};
using Shape = std::vector<Point>;
using Shapes = std::vector<Shape>;

bool is_triangle(const Shape&);
bool is_rectangle(const Shape&);
bool is_square(const Shape&);
bool compare(const Shape& first, const Shape& second);
void print_shapes(Shapes& shapes, std::ostream& out);
void print_points(std::vector<Point>& points, std::ostream& out);
std::istream& operator>>(std::istream& in, Shape& shape);
std::istream& operator>>(std::istream& in, Point& point);
std::ostream& operator<<(std::ostream& out, const Point& point);
std::ostream& operator<<(std::ostream& out, const Shape& shape);

#endif //B5_SHAPE_HPP
