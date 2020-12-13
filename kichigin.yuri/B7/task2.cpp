#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <iterator>
#include "shape.hpp"
#include "circle.hpp"
#include "triangle.hpp"
#include "square.hpp"
#include "skip.hpp"

std::istream& operator>>(std::istream& in, std::shared_ptr<Shape>& shape);
std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Shape>& shape);

void task2()
{
  using namespace std::placeholders;

  std::list<std::shared_ptr<Shape>> list{ std::istream_iterator<std::shared_ptr<Shape>>(std::cin), std::istream_iterator<std::shared_ptr<Shape>>() };
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading");
  }

  std::cout << "Original:\n";
  std::copy(list.begin(), list.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Left-Right:\n";
  list.sort(std::bind(&Shape::isMoreLeft, std::bind(&std::shared_ptr<Shape>::operator*, _1),
      std::bind(&std::shared_ptr<Shape>::operator*, _2)));
  std::copy(list.begin(), list.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Right-Left:\n";
  list.reverse();
  std::copy(list.begin(), list.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Top-Bottom:\n";
  list.sort(std::bind(&Shape::isUpper, std::bind(&std::shared_ptr<Shape>::operator*, _1), 
      std::bind(&std::shared_ptr<Shape>::operator*, _2)));
  std::copy(list.begin(), list.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));

  std::cout << "Bottom-Top:\n";
  list.reverse();
  std::copy(list.begin(), list.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout));
}

std::shared_ptr<Shape> createShape(std::string& shapeName, point_t& point)
{
  if (shapeName == "CIRCLE")
  {
    return std::make_shared<Circle>(point);
  }
  if (shapeName == "SQUARE")
  {
    return std::make_shared<Square>(point);
  }
  if (shapeName == "TRIANGLE")
  {
    return std::make_shared<Triangle>(point);
  }
  return nullptr;
}

std::istream& operator>>(std::istream& in, std::shared_ptr<Shape>& shape)
{
  in >> std::ws;
  if (in.peek() == EOF)
  {
    in.setstate(in.eofbit);
    return in;
  }
  std::string shapeName;
  while (in.peek() != '(' && !std::isblank(in.peek()))
  {
    if (in.peek() == '\n')
    {
      in.setstate(std::ios::failbit);
      break;
    }
    else
    {
      shapeName += in.get();
    }
  }
  point_t point;
  in >> point;
  if (in.fail())
  {
    return in;
  }
  std::shared_ptr<Shape> newShape = createShape(shapeName, point);
  if (newShape == nullptr)
  {
    in.setstate(in.failbit);
    return in;
  }
  shape = std::move(newShape);
  return in;
}

std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Shape>& shape)
{
  shape->draw(out);
  return out;
}
