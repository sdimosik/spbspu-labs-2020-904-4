#include "shape.hpp"

bool isTriangle(const Shape &shape)
{
  return (shape.points.size() == 3);
}

bool isRectangle(Shape &shape)
{
  if (shape.points.size() != 4)
  {
    return false;
  }

  return sqrt(pow((shape.points[0].x - shape.points[2].x), 2) + pow(((shape.points[0].y - shape.points[2].y)), 2)) ==
         sqrt(pow((shape.points[1].x - shape.points[3].x), 2) + pow(((shape.points[1].y - shape.points[3].y)), 2));
}

bool isSquare(Shape &shape)
{
  if (shape.points.size() != 4)
  {
    return false;
  }

  return sqrt(pow((shape.points[0].x - shape.points[1].x), 2) + pow(((shape.points[0].y - shape.points[1].y)), 2)) ==
         sqrt(pow((shape.points[0].x - shape.points[3].x), 2) + pow(((shape.points[0].y - shape.points[3].y)), 2));
}

std::istream &operator>>(std::istream &in, Shape &shape)
{
  size_t tops;
  in >> std::ws >> tops;
  if (in.peek() == EOF || in.fail())
  {
    return in;
  }
  if(tops < 3)
  {
    throw std::invalid_argument("Invalid count of vertices!");
  }

  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(in), tops, std::back_inserter(temp));
  shape.points.swap(temp);

  if (isTriangle(shape))
  {
    shape.type = Shape::TRIANGLE;
  }
  else if (isSquare(shape))
  {
    shape.type = Shape::SQUARE;
  }
  else if (isRectangle(shape))
  {
    shape.type = Shape::RECTANGLE;
  }
  else
  {
    shape.type = Shape::OTHER;
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
  if (shape1.type == shape2.type)
  {
    return shape1.points[0].x < shape2.points[0].x;
  }
  return (shape1.type < shape2.type);
}
