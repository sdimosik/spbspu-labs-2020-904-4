#include <cctype>
#include "shape.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "utils.hpp"
#include "flagGuard.hpp"

Shape::Shape(const int x, const int y) :
  x_(x),
  y_(y)
{}

bool Shape::isMoreLeft(const Shape &shape) const
{
  return x_ < shape.x_;
}

bool Shape::isUpper(const Shape &shape) const
{
  return y_ > shape.y_;
}

std::ostream &operator<<(std::ostream &ostream, const std::shared_ptr<Shape> &shape)
{
  shape->draw(ostream);
  return ostream;
}

std::shared_ptr<Shape> getShapeByType(const std::string &type, const int x, const int y)
{
  if (type == "CIRCLE")
  {
    return std::make_shared<Circle>(Circle(x, y));
  }
  if (type == "SQUARE")
  {
    return std::make_shared<Square>(Square(x, y));
  }
  if (type == "TRIANGLE")
  {
    return std::make_shared<Triangle>(Triangle(x, y));
  }
  throw std::invalid_argument("Wrong format type: " + type);
}

std::istream &operator>>(std::istream &in, std::shared_ptr<Shape> &shape)
{
  std::string type;
  in >> std::ws;
  
  if (in.peek() == EOF)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  
  while (in.peek() != '(' && !std::isblank(in.peek()))
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios::failbit);
      break;
    }
    type += static_cast<char>(in.get());
  }
  
  FlagGuard guard = FlagGuard(in);
  in.unsetf(std::ios::skipws);
  
  in >> utils::space;
  if (in.get() != '(')
  {
    in.setstate(std::ios::failbit);
  }
  
  int x;
  in >> utils::space >> x >> utils::space;
  if (in.get() != ';')
  {
    in.setstate(std::ios::failbit);
  }
  
  int y;
  in >> utils::space >> y >> utils::space;
  if (in.get() != ')')
  {
    in.setstate(std::ios::failbit);
  }
  
  shape = getShapeByType(type, x, y);
  return in;
}
