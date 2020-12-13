#include <cctype>
#include "shape.hpp"
#include "circle.hpp"
#include "square.hpp"
#include "triangle.hpp"
#include "flagGuard.hpp"
#include "../common/tools.hpp"

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

std::ostream &operator<<(std::ostream &out, const std::shared_ptr<Shape> &shape)
{
  shape->draw(out);
  return out;
}

std::shared_ptr<Shape> createShape(const std::string &type, const int x, const int y)
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
  throw std::invalid_argument("Task 2. Invalid input!\n");

}

std::istream &operator>>(std::istream &in, std::shared_ptr<Shape> &shape)
{
  std::string name;
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
    else
    {
      name += in.get();
    }
  }

  FlagGuard guard = FlagGuard(in);
  in.unsetf(std::ios::skipws);
  in >> skipSpace;

  if (in.get() != '(')
  {
    in.setstate(std::ios::failbit);
  }

  int x;

  in >> skipSpace >> x >> skipSpace;

  if (in.get() != ';')
  {
    in.setstate(std::ios::failbit);
  }

  int y;

  in >> skipSpace >> y >> skipSpace;

  if (in.get() != ')')
  {
    in.setstate(std::ios::failbit);
  }

  shape = createShape(name, x, y);

  return in;
}
