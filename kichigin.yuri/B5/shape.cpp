#include "shape.hpp"
#include <iostream>
#include <algorithm>
#include <cctype>
#include "checks.hpp"

namespace details
{
  std::istream& myWs(std::istream& in)
  {
    while (std::isblank(in.peek()))
    {
      in.get();
    }
    return in;
  }

  void skipEmptyLines(std::istream& in)
  {
    if (!in.fail())
    {
      while (!in.eof() && in.peek() == '\n')
      {
        in.get();
      }
    }
  }
}

std::istream& operator>>(std::istream& in, Point& point)
{
  in.unsetf(std::ios_base::skipws);
  char symbol = '\0';
  in >> details::myWs >> symbol;
  if (symbol != '(')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  in >> details::myWs >> point.x >> details::myWs >> symbol;
  if (symbol != ';')
  {
    in.setstate(in.failbit);
    return in;
  }

  in >> details::myWs >> point.y >> details::myWs >> symbol;
  if (symbol != ')')
  {
    in.setstate(in.failbit);
    return in;
  }

  in.setf(std::ios_base::skipws);
  return in;
}

void printPointVector(const std::vector<Point>& pointVector, std::ostream& out)
{
  std::for_each(pointVector.begin(), pointVector.end(), [&out](const Point& point)
    {
      out << " (" << point.x << ';' << point.y << ')';
    });
  out << '\n';
}

std::istream& operator>>(std::istream& in, Shape& shape)
{
  size_t vertices = 0;
  in >> std::ws >> vertices;

  if (in.peek() == EOF)
  {
    return in;
  }

  if (in.fail())
  {
    return in;
  }

  if (vertices < Shape::MIN_VERTICES)
  {
    in.setstate(in.failbit);
    return in;
  }

  Shape newShape;
  for (size_t i = 0; i < vertices; i++)
  {
    Point point;
    in >> point;
    if (in.fail())
    {
      return in;
    }
    newShape.points.push_back(point);
  }

  if (isTriangle(newShape))
  {
    newShape.type = Shape::TRIANGLE;
  }
  else if (isSquare(newShape))
  {
    newShape.type = Shape::SQUARE;
  }
  else if (isRectangle(newShape))
  {
    newShape.type = Shape::RECTANGLE;
  }
  else if (isPentagon(newShape))
  {
    newShape.type = Shape::PENTAGON;
  }
  else
  {
    newShape.type = Shape::COMMON;
  }

  shape = newShape;
  return in;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  out << shape.points.size();
  printPointVector(shape.points, out);
  return out;
}

bool operator<(const Shape& leftShape, const Shape& rightShape)
{
  if (leftShape.type == Shape::COMMON)
  {
    return leftShape.points.size() < rightShape.points.size();
  }

  return leftShape.type < rightShape.type;
}

bool operator>(const Shape& leftShape, const Shape& rightShape)
{
  return (rightShape < leftShape);
}

bool operator==(const Shape& leftShape, const Shape& rightShape)
{
  if (leftShape.type == Shape::COMMON)
  {
    return leftShape.points.size() == rightShape.points.size();
  }

  return leftShape.type == rightShape.type;
}

bool operator!=(const Shape& leftShape, const Shape& rightShape)
{
  return !(leftShape == rightShape);
}

bool operator<=(const Shape& leftShape, const Shape& rightShape)
{
  return ((leftShape < rightShape) || (leftShape == rightShape));
}

bool operator>=(const Shape& leftShape, const Shape& rightShape)
{
  return ((leftShape > rightShape) || (leftShape == rightShape));
}
