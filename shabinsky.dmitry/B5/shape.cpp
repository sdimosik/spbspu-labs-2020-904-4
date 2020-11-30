#include "shape.hpp"

const size_t TRIANGLE_VERT = 3;
const size_t SQUARE_VERT = 4;
const size_t PENTAGON_VERT = 5;

bool isSquare(Shape &shape)
{
  return sqrt(pow((shape.points[0].x - shape.points[1].x), 2) + pow(((shape.points[0].y - shape.points[1].y)), 2)) ==
         sqrt(pow((shape.points[0].x - shape.points[3].x), 2) + pow(((shape.points[0].y - shape.points[3].y)), 2));
}

bool isRectangle(Shape &shape)
{
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
{/*
  std::string line;
  getline(in, line);
  line.erase(std::remove(line.begin(), line.end(), '\t'), line.end());
  line.erase(std::remove(line.begin(), line.end(), ' '), line.end());
  std::stringstream sin(line);*/
  size_t vert;
  /*sin >> vert;*/
  in >> std::ws >> vert;
  if (in.peek() == EOF || in.fail())
  {
    return in;
  }
  
  vert < TRIANGLE_VERT ? throw std::invalid_argument("bad vertices count") : 0;
  
  //shape.points = {std::istream_iterator<Point>(sin), std::istream_iterator<Point>()};
  std::vector<Point> temp;
  std::copy_n(std::istream_iterator<Point>(in), vert, std::back_inserter(temp));
  shape.points.swap(temp);
  shape.points.size() != vert ? throw std::invalid_argument("points count cant be less or more than vertices") : 0;
  
  switch (shape.points.size())
  {
    case TRIANGLE_VERT:
      shape.type = Shape::Type::TRIANGLE;
      break;
    case SQUARE_VERT:
      if (isSquare(shape))
      {
        shape.type = Shape::Type::SQUARE;
      }
      else if (isRectangle(shape))
      {
        shape.type = Shape::Type::RECTANGLE;
      }
      break;
    case PENTAGON_VERT:
      shape.type = Shape::Type::PENTAGON;
      break;
    default:
      shape.type = Shape::Type::POLYGON;
      break;
  }
  return in;
}

bool operator<(const Shape &lhs, const Shape &rhs)
{
  return (lhs.type < rhs.type);
}
