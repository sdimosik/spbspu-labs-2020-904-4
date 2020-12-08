#include "point.hpp"
#include "blanks.hpp"

std::istream& operator>>(std::istream& in, Point& point)
{
  in >> blank;
  if (!in.eof())
  {
    char symbol;
    in >> symbol >> blank;
    if (symbol == '('  && in.peek() != '\n')
    {
      int x;
      if (in >> x >> blank && in.peek() != '\n')
      {
        in >> symbol >> blank;
        if (symbol == ';' && in.peek() != '\n')
        {
          int y;
          if (in >> y >> blank && in.peek() != '\n')
          {
            in >> symbol;
            if (symbol == ')')
            {
              point = { x,y };
              return in;
            }
          }
        }
      }
    }
  }
  in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  out << " (" << point.x << ";" << point.y << ")";
  return out;
}
