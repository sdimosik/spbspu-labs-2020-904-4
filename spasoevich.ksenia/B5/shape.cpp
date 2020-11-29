#include "shape.hpp"

std::ostream& operator<<(std::ostream& output, const Shape& shape)
{
  output << shape.points.size() << " ";
  std::copy(shape.points.begin(), shape.points.end(), std::ostream_iterator<Point>(output));
  output << std::endl;
  return output;
}

std::istream& operator>>(std::istream& input, Shape& shape)
{
  size_t tops;
  input >> tops; 

  if (input.eof())
  {
    return input;
  }

  if (tops < TRIANGLE_VERTICES)
  {
    throw std::invalid_argument("Invalid amount of tops!\n");
  }


  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(input), tops, std::back_inserter(temp));
  shape.points.swap(temp);

  switch (shape.points.size())
  {
  case TRIANGLE_VERTICES:
    shape.shapeType = Shape::Shapes::TRIANGLE;
    break;

  case SQUARE_VERTICES:
    if (isSquare(shape))
    {
      shape.shapeType = Shape::Shapes::SQUARE;
    }
    else if (isRectangle(shape))
    {
      shape.shapeType = Shape::Shapes::RECTANGLE;
    }
    break;

  case PENTAGON_VERTICES:
    shape.shapeType = Shape::Shapes::PENTAGON;
    break;

  default:
    shape.shapeType = Shape::Shapes::DEFAULT;
    break;
  }
  return input;
}

bool operator<(const Shape& left, const Shape& right)
{
  return left.shapeType < right.shapeType;
}

bool isTriangle(Shape& shape)
{
  return (shape.points.size() == 3);
}

bool isSquare(const Shape& shape)
{
  if (shape.points.size() != 4)
    return false;

 return sqrt(pow((shape.points[0].x - shape.points[1].x), 2) + pow(((shape.points[0].y - shape.points[1].y)), 2))== sqrt(pow((shape.points[0].x - shape.points[3].x), 2) + pow(((shape.points[0].y - shape.points[3].y)), 2));
}

bool isRectangle(const Shape& shape)
{
  if (shape.points.size() != 4)
    return false;

return sqrt(pow((shape.points[0].x - shape.points[2].x), 2) + pow(((shape.points[0].y - shape.points[2].y)), 2))==sqrt(pow((shape.points[1].x - shape.points[3].x), 2) + pow(((shape.points[1].y - shape.points[3].y)), 2));;
}

bool isPentagon(const Shape& shape)
{
  return (shape.points.size() == 5);
}
