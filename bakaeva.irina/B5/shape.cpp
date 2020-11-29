#include "shape.hpp"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <cmath>
#include <string>
#include <iterator>

std::istream &operator>>(std::istream &in, Shape &shape)
{
  size_t verticesCount;

  in >> verticesCount;

  if (in.eof()) 
  {
    return in;
  }

  if (verticesCount < MIN_COUNT_OF_POINTS)
  {
    throw std::invalid_argument("Invalid vertices!");
  }

  std::vector<point_t> temp;

  std::copy_n(std::istream_iterator<point_t>(in), verticesCount, std::back_inserter(temp));

  shape.points.swap(temp);

  switch (shape.points.size())
  {
    case TRIANGLE_VERT:
      shape.type = Shape::ShapeType::TRIANGLE;
      break;
    case QUADRANGLE_VERT:
      if (isRectangle(shape))
      {
        if (isSquare(shape))
        {
          shape.type = Shape::ShapeType::SQUARE;
        }
        else
        {
          shape.type = Shape::ShapeType::RECTANGLE;
        }
      }
      break;
    case PENTAGON_VERT:
      shape.type = Shape::ShapeType::PENTAGON;
      break;
    default:
      shape.type = Shape::ShapeType::OTHER;
      break;
  }

  return in;
}

bool operator<(const Shape &shape1, const Shape &shape2)
{
  return shape1.type < shape2.type;
}

bool isRectangle(const Shape &shape)
{
  if (shape.points.size() != QUADRANGLE_VERT)
  {
    return false;
  }

  bool compareSide1 = (getSideLength(shape.points[0], shape.points[1]) ==
      getSideLength(shape.points[2], shape.points[3]));
  bool compareSide2 = (getSideLength(shape.points[1], shape.points[2]) ==
      getSideLength(shape.points[0], shape.points[3]));
  bool compareDiag = (getSideLength(shape.points[0], shape.points[2]) ==
      getSideLength(shape.points[1], shape.points[3]));

  return compareDiag && compareSide1 && compareSide2;
}

bool isSquare(const Shape &shape)
{
  if (shape.points.size() != QUADRANGLE_VERT)
  {
    return false;
  }

  return sqrt(pow((shape.points[0].x - shape.points[1].x), 2) + pow(((shape.points[0].y - shape.points[1].y)), 2)) ==
      sqrt(pow((shape.points[0].x - shape.points[3].x), 2) + pow(((shape.points[0].y - shape.points[3].y)), 2));
}

int getSideLength(const point_t &point1, const point_t &point2)
{
  int x = point1.x - point2.x;
  int y = point1.x - point2.x;

  return x * x + y * y;
}
