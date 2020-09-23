#ifndef HW01_BASE_TYPES_H
#define HW01_BASE_TYPES_H

#include <ostream>

namespace shabinsky
{
  struct point_t
  {
    double x, y;
    
    friend bool operator==(const point_t &point1, const point_t &point2)
    {
      return point1.x == point2.x &&
             point1.y == point2.y;
    }
  };
  
  struct rectangle_t
  {
    double width, height;
    point_t pos;
    
    friend bool operator==(const rectangle_t &rectangle1, const rectangle_t &rectangle2)
    {
      return rectangle1.width == rectangle2.width &&
             rectangle1.height == rectangle2.height &&
             rectangle1.pos == rectangle2.pos;
    }
  };
  
  inline std::ostream &operator<<(std::ostream &out, const point_t &point)
  {
    out << "(X: " << point.x << ";Y: " << point.y << ")";
    return out;
  }
  
  inline std::ostream &operator<<(std::ostream &out, const rectangle_t &rectangle)
  {
    out << "[H: " << rectangle.height << ";W: " << rectangle.width << ";" << rectangle.pos << "]";
    return out;
  }
}
#endif //HW01_BASE_TYPES_H
