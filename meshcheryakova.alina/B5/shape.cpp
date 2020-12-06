#include "shape.hpp"
#include <math.h>
#include <algorithm>
#include "detail.hpp"

std::istream& operator>>(std::istream& in, Shape& shape)
{
  int count_of_points;
  in >> std:: ws >> count_of_points;

  if(in.peek() == std::char_traits<char>::eof())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }

  while(in.peek() != std::char_traits<char>::eof() && in.peek() == '\n')
  {
    in.get();
  }

  if(count_of_points < 3)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  Point point;
  Shape new_shape;
  while(count_of_points > 0)
  {
    in >> point;
    new_shape.push_back(point);
    count_of_points--;
  }
  shape = new_shape;
  return in;
}

std::istream& operator>>(std::istream& in, Point& point)
{
  if(in.peek() == std::char_traits<char>::eof())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  int pos;
  in >> blank;
  if(in.peek() != '(')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.ignore(1);
  in >> blank >> pos >> blank;
  if(in.peek() != ';')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.ignore(1);
  point.x = pos;
  in >> blank >> pos >> blank;
  if(in.peek() != ')')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.ignore(1);
  point.y = pos;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  out << "(" << point.x << ";" << point.y << ")";
  return out;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  out << shape.size() << "  ";
  std::for_each(shape.begin(), shape.end(), [&out](const Point& point)
  {
    out << point;
    out << "  ";
  });
  out << '\n';
  return  out;
}

bool is_triangle(const Shape& shape)
{
  bool in_line = true;
  if(shape.size() == 3)
  {
    for(const auto &elem :shape)
    {
      if(elem.x != shape.front().x)
      {
        in_line = false;
      }
    }

    for(const auto &elem :shape)
    {
      if(elem.y != shape.front().y && !in_line)
      {
        return true;
      }
    }
  }
  return false;
}


bool is_rectangle(const Shape& shape)
{
  if(shape.size() != 4)
  {
    return false;
  }
  int width_top = std::abs(shape[2].x - shape[1].x);
  int width_bot = std::abs(shape[3].x - shape[0].x);
  int length_left = std::abs(shape[1].y - shape[0].y);
  int length_right = std::abs(shape[2].y - shape[3].y);

  if(width_bot != width_top && length_left != length_right)
  {
    return false;
  }
  else
  {
    int diagonal_1 = std::pow(std::abs(shape[1].x - shape[2].x),2) + std::pow(std::abs(shape[1].y - shape[0].y),2);
    int diagonal_2 = std::pow(std::abs(shape[3].x - shape[0].x),2) + std::pow(std::abs(shape[2].y - shape[3].y),2);
    if(diagonal_1 == diagonal_2)
    {
      return true;
    }
  }
 return false;
}

bool is_square(const Shape& shape)
{
  if(is_rectangle(shape))
  {
    return std::abs(shape[0].x - shape[3].x) == std::abs(shape[1].y - shape[0].y);
  }
  return false;
}

bool compare(const Shape& first, const Shape& second)
{
  if (second.size() != 3)
  {
    if ((first.size() == 3))
    {
      return true;
    }

    if (is_square(first) && (!is_square(second)))
    {
      return true;
    }

    if ((is_rectangle(first)) && (!is_rectangle(second)))
    {
      return true;
    }
  }

  return false;
}

void print_shapes(Shapes& shapes, std::ostream& out)
{
  std::for_each(shapes.begin(), shapes.end(), [&out](const Shape& shape)
  {
    out << shape;
  });
}

void print_points(std::vector<Point>& points, std::ostream& out)
{
  std::for_each(points.begin(), points.end(), [&out](const Point& point)
  {
    out << point;
    out << "  ";
  });
}
