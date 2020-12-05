#include "shape.hpp"
#include <cmath>
#include <iterator>
#include <algorithm>

const size_t TRIANGLE_TOPS = 3;
const size_t RECTANGLE_TOPS = 4;

bool isTriangle(const Shape &shape);

bool isRectangle(const Shape &shape);

bool isSquare(const Shape &shape);

std::istream &operator>>(std::istream &in, Shape &shape)
{
  size_t tops;
  in >> std::ws >> tops;

  if (in.peek() == EOF)
  {
    return in;
  }

  if (tops < TRIANGLE_TOPS)
  {
    throw std::invalid_argument("Error: entered invalid count of vertices!");
  }

  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(in), tops, std::back_inserter(temp));
  shape.points.swap(temp);

  switch (shape.points.size())
  {
    case TRIANGLE_TOPS:
      if(isTriangle(shape))
      {
        shape.type = Shape::TRIANGLE;
      }
      break;
    case RECTANGLE_TOPS:
      if (isSquare(shape))
      {
        shape.type = Shape::SQUARE;
      }
      else if (isRectangle(shape))
      {
        shape.type = Shape::RECTANGLE;
      }
      break;
    default:
      shape.type = Shape::OTHER;
      break;
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const Shape &shape)
{
  out << shape.points.size() << " ";
  std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(out));
  out << "\n";
  return out;
}

bool operator<(const Shape &shape1, const Shape &shape2)
{
  return shape1.type < shape2.type;
}

bool isTriangle(const Shape &shape)
{
  return (shape.points.size() == 3);
}

bool isRectangle(const Shape &shape)
{
  if (shape.points.size() != RECTANGLE_TOPS)
  {
    return false;
  }
  return sqrt(pow((shape.points[0].x - shape.points[2].x), 2) + pow(((shape.points[0].y - shape.points[2].y)), 2)) ==
      sqrt(pow((shape.points[1].x - shape.points[3].x), 2) + pow(((shape.points[1].y - shape.points[3].y)), 2));
}

bool isSquare(const Shape &shape)
{
  if (shape.points.size() != RECTANGLE_TOPS)
  {
    return false;
  }
  return sqrt(pow((shape.points[0].x - shape.points[1].x), 2) + pow(((shape.points[0].y - shape.points[1].y)), 2)) ==
      sqrt(pow((shape.points[0].x - shape.points[3].x), 2) + pow(((shape.points[0].y - shape.points[3].y)), 2));
}

