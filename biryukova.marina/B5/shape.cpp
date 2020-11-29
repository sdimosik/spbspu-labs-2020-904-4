#include "shape.hpp"
#include <cmath>
#include <iostream>
#include <iterator>
#include <string>
#include <algorithm>

size_t getDistance(const std::pair<int, int>& pair)
{
  return (sqrt(pow(pair.first, 2) + pow(pair.second, 2)));
}

int count(int currentSum, const Shape& shape)
{
  return (currentSum + shape.points.size());
}

bool isTriangle(const Shape& shape)
{
  return (shape.points.size() == 3);
}

bool isSquare(const Shape& shape)
{
  if (shape.points.size() != 4)
  {
    return false;
  }
  const std::pair<int, int> side1 = std::make_pair(shape.points[0].x - shape.points[1].x, 
      shape.points[0].y - shape.points[1].y);
  const std::pair<int, int> side2 = std::make_pair(shape.points[0].x - shape.points[3].x, 
      shape.points[0].y - shape.points[3].y);
  const std::pair<int, int> diag1 = std::make_pair(shape.points[0].x - shape.points[2].x, 
      shape.points[0].y - shape.points[2].y);
  const std::pair<int, int> diag2 = std::make_pair(shape.points[1].x - shape.points[3].x, 
      shape.points[1].y - shape.points[3].y);
  return ((getDistance(side1) == getDistance(side2)) && (getDistance(diag1) == getDistance(diag2)));
}

bool isRectangle(const Shape& shape)
{
  if (shape.points.size() != 4)
  {
    return false;
  }
  const std::pair<int, int> diag1 = std::make_pair(shape.points[0].x - shape.points[2].x, 
      shape.points[0].y - shape.points[2].y);
  const std::pair<int, int> diag2 = std::make_pair(shape.points[1].x - shape.points[3].x, 
      shape.points[1].y - shape.points[3].y);
  return (getDistance(diag1) == getDistance(diag2));
}

bool isPentagon(const Shape& shape)
{
  return (shape.points.size() == 5);
}

const Point& getFirstPoint(const Shape& shape)
{
  return shape.points.front();
}

bool comparator(const Shape& lhs, const Shape& rhs)
{
  if (lhs.type == rhs.type)
  {
    return lhs.points[0].x < rhs.points[0].x;
  }
  return (lhs.type < rhs.type);
}

std::ostream& operator <<(std::ostream& out, const Shape& shape)
{
  out << shape.points.size() << " ";
  std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(out, " "));
  return out;
}

std::istream& operator >>(std::istream& in, Shape& shape)
{
  size_t vertices;
  in >> std::ws >> vertices;
  if (in.peek() == EOF)
  {
    return in;
  }
  if (in.fail())
  {
    return in;
  }
  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(in), vertices, std::back_inserter(temp));
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
