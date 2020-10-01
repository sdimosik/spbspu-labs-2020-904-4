
#ifndef BASE_TYPES_HPP
#define BASE_TYPES_HPP

namespace pashnin
{
  
  struct point_t
  {
    double x, y;
    
    bool operator==(const point_t &dot) const
    {
      return (this->x == dot.x && this->y == dot.y);
    }
  };
  
  struct rectangle_t
  {
    double width, height;
    point_t pos;
  };
  
}

#endif
