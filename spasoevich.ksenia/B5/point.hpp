#ifndef POINT_HPP
#define POINT_HPP

#include <iostream>
#include <stdexcept>
#include <cctype>

struct Point
{
  int x, y; 
};

std::istream& deleteBlanks(std::istream& in);
std::istream& operator>>(std::istream& in, Point& point);
std::ostream& operator<<(std::ostream& out, const Point& point);

#endif
