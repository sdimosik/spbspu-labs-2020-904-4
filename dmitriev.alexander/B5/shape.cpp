#include "shape.hpp"

const size_t TRIANGLE_VERTICES = 3;
const size_t SQUARE_VERTICES = 4;
const size_t PENTAGON_VERTICES = 5;

bool isSquare(Shape &shape)
{
  if (shape.points.size() != SQUARE_VERTICES)
  {
    return false;
  }
  return sqrt(pow((shape.points[0].x - shape.points[1].x), 2) + pow(((shape.points[0].y - shape.points[1].y)), 2)) ==
         sqrt(pow((shape.points[0].x - shape.points[3].x), 2) + pow(((shape.points[0].y - shape.points[3].y)), 2));
}

bool isRectangle(Shape &shape)
{
  if (shape.points.size() != SQUARE_VERTICES)
  {
    return false;
  }
  return sqrt(pow((shape.points[0].x - shape.points[2].x), 2) + pow(((shape.points[0].y - shape.points[2].y)), 2)) ==
         sqrt(pow((shape.points[1].x - shape.points[3].x), 2) + pow(((shape.points[1].y - shape.points[3].y)), 2));
}

std::ostream &operator<<(std::ostream &ostream, const Shape &shape)
{
  ostream << shape.points.size() << " ";
  std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(ostream));
  ostream << std::endl;
  return ostream;
}

std::istream &operator>>(std::istream &in, Shape &shape)
{
  in >> std::ws;
  if (in.peek() == EOF)
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  size_t vertices;
  in >> vertices;
  if (vertices < TRIANGLE_VERTICES)
  {
    in.setstate(std::ios::failbit);
  }
  std::vector<Point> tmp;
  std::copy_n(std::istream_iterator<Point>(in), vertices, std::back_inserter(tmp));
  shape.points.swap(tmp);

  if (shape.points.size() != vertices)
  {
    in.setstate(std::ios::failbit);
  }
  switch (shape.points.size())
  {
    case TRIANGLE_VERTICES:
      shape.type = Shape::ShapeType::TRIANGLE;
      break;
    case SQUARE_VERTICES:
      if (isSquare(shape))
      {
        shape.type = Shape::ShapeType::SQUARE;
      } else if (isRectangle(shape))
      {
        shape.type = Shape::ShapeType::RECTANGLE;
      }
      break;
    case PENTAGON_VERTICES:
      shape.type = Shape::ShapeType::PENTAGON;
      break;
    default:
      shape.type = Shape::ShapeType::POLYGON;
      break;
  }
  return in;
}

bool operator<(const Shape &lhs, const Shape &rhs)
{
  return (lhs.type < rhs.type);
}
