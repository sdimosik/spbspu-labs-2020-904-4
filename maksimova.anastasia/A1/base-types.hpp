#ifndef base_types_hpp
#define base_types_hpp
#include <iostream>

struct point_t
{
  double x;
  double y;
};

struct rectangle_t
{
  double width;
  double height;
  point_t pos;
  void print()
  {
    std::cout << "Width = " << width << ", " << "Height = " << height
        << ", " << "Position (" << pos.x << ", " << pos.y << ")\n";
  }
};

#endif
