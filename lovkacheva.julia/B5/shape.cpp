#include "shape.hpp"
#include <iterator>
#include <sstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <unordered_map>
#include <cmath>
#include "utilities.hpp"

std::istream& lovkacheva::operator>>(std::istream& in, lovkacheva::Point& point)
{
  in >> std::ws;
  char character = in.get();
  if(character != '(')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  skipNonNewlineWs(in);
  int x = 0;
  in >> x;
  if (in.fail() || in.eof())
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  skipNonNewlineWs(in);
  character = in.get();
  if ( character != ';')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  skipNonNewlineWs(in);
  int y = 0;
  in >> y;
  if (in.fail() || in.eof())
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  skipNonNewlineWs(in);
  character = in.get();
  if(character != ')')
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  point.x = x;
  point.y = y;
  return in;
}

std::istream& lovkacheva::operator>>(std::istream& in, lovkacheva::Shape& shape)
{
  in >> std::ws;
  if (in.eof())
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  size_t size = 0;
  in >> size;
  if (in.fail())
  {
    return in;
  }
  skipNonNewlineWs(in);
  std::vector<Point> tempShape(size);
  std::istream_iterator<Point> inIt(in);
  std::copy_n(inIt, size, tempShape.begin());
  if (in.fail())
  {
    in.clear();
    in.setstate(std::ios::failbit);
    return in;
  }
  shape = std::move(tempShape);
  return in;
}

std::ostream& lovkacheva::operator<<(std::ostream& out, const Point& point)
{
  out << '(' << point.x << "; " << point.y << ')';
  return out;
}

std::ostream& lovkacheva::operator<<(std::ostream& out, const Shape& shape)
{
  out << shape.size() << ' ';
  std::ostream_iterator<Point> outIt(out, " ");
  std::copy(shape.begin(), shape.end(), outIt);
  return out;
}

bool lovkacheva::compareShapes(const Shape& lhs, const Shape& rhs)
{
  ShapeType lhsType = getType(lhs);
  ShapeType rhsType = getType(rhs);
  if (lhsType == rhsType)
  {
    return lhs[0].x > rhs[0].x;
  }
  return lhsType < rhsType;
}

int lovkacheva::squareDistance(const Point& a, const Point& b)
{
  return (square(a.x - b.x) + square(a.y - b.y));
}

bool lovkacheva::isTriangle(const Shape& shape)
{
  if (shape.size() != 3)
  {
    return false;
  }
  return true;
}

bool lovkacheva::isRectangle(const Shape& shape)
{
  if (shape.size() != 4)
  {
    return false;
  }
  return (squareDistance(shape[0], shape[1]) == squareDistance(shape[2], shape[3])
      && (squareDistance(shape[0], shape[2]) == squareDistance(shape[1], shape[3]))
      && (squareDistance(shape[1], shape[2]) == squareDistance(shape[0], shape[3])));
}

bool lovkacheva::isSquare(const Shape& shape)
{
  if (!isRectangle(shape))
  {
    return false;
  }
  int firstEdge = squareDistance(shape[0], shape[1]);
  int secondEdge = squareDistance(shape[0], shape[3]);
  return firstEdge == secondEdge;
}

lovkacheva::ShapeType lovkacheva::getType(const Shape& shape)
{
  if (isTriangle(shape))
  {
    return ShapeType::TRIANGLE;
  }
  if (isSquare(shape))
  {
    return ShapeType::SQUARE;
  }
  if (isRectangle(shape))
  {
    return ShapeType::RECTANGLE;
  }
  return ShapeType::OTHER;
}
