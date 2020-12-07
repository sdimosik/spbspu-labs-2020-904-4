#include "shape.hpp"

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cmath>
#include <algorithm>
#include <iterator>

std::istream& operator>>(std::istream& in, Shape& shape)
{
  size_t amountOfVertices;
  in >> std::ws >> amountOfVertices;
  if((in.peek() == EOF) || in.fail())
  {
    return in;
  }
  if(amountOfVertices < 3)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(in), amountOfVertices, std::back_inserter(temp));
  shape.points.swap(temp);
  if(amountOfVertices == 3)
  {
    shape.typeOfShape = Shape::TypeOfShape::TRIANGLE;
  }
  else if(isSquare(shape))
  {
    shape.typeOfShape = Shape::TypeOfShape::SQUARE;
  }
  else if(isRectangle(shape))
  {
    shape.typeOfShape = Shape::TypeOfShape::RECTANGLE;
  }
  else if(amountOfVertices == 5)
  {
    shape.typeOfShape = Shape::TypeOfShape::PENTAGON;
  }
  else
  {
    shape.typeOfShape = Shape::TypeOfShape::POLYGON;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  out << shape.points.size() << ' ';
  std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(out, " "));
  return out;
}

bool isRectangle(const Shape& shape)
{
  if(shape.points.size() != 4)
  {
    return false;
  }
  using geometricVector = Point;
  geometricVector ab = {shape.points.at(1).x - shape.points.at(0).x, shape.points.at(1).y - shape.points.at(0).y};
  geometricVector bc = {shape.points.at(2).x - shape.points.at(1).x, shape.points.at(2).y - shape.points.at(1).y};
  geometricVector cd = {shape.points.at(3).x - shape.points.at(2).x, shape.points.at(3).y - shape.points.at(2).y};
  geometricVector da = {shape.points.at(0).x - shape.points.at(3).x, shape.points.at(0).y - shape.points.at(3).y};

  return ((ab.x * bc.x + ab.y * bc.y == 0) &&
      (bc.x * cd.x + bc.y * cd.y == 0) &&
      (cd.x * da.x + cd.y * da.y == 0));
}

bool isSquare(const Shape& shape)
{
  if(!isRectangle(shape))
  {
    return false;
  }

  int squaredAB = pow((shape.points.at(1).x - shape.points.at(0).x),2)
      +  pow((shape.points.at(1).y - shape.points.at(0).y),2);
  int squaredBC = pow((shape.points.at(2).x - shape.points.at(1).x),2)
      +  pow((shape.points.at(2).y - shape.points.at(1).y),2);
  int squaredCD = pow((shape.points.at(3).x - shape.points.at(2).x),2)
      +  pow((shape.points.at(3).y - shape.points.at(2).y),2);
  int squaredDA = pow((shape.points.at(0).x - shape.points.at(3).x),2)
      +  pow((shape.points.at(0).y - shape.points.at(3).y),2);
  return ((squaredAB == squaredBC) && (squaredAB == squaredCD) && (squaredAB == squaredDA));
}

bool operator<(const Shape& first, const Shape& second)
{
  return first.typeOfShape < second.typeOfShape;
}
