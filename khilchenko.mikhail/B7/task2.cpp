#include <vector>
#include <iterator>
#include <algorithm>
#include <string>
#include <boost/algorithm/string/trim.hpp>
#include <map>
#include <functional>

#include "triangle.hpp"
#include "circle.hpp"
#include "square.hpp"

const static std::map<std::string, std::function<std::shared_ptr<Shape>(const Point&)>> constructors
    = {
        {"CIRCLE", [](const Point& point)
          {
            return std::make_shared<Circle>(point);
          }},
        {"TRIANGLE", [](const Point& point)
          {
            return std::make_shared<Triangle>(point);
          }},
        {"SQUARE", [](const Point& point)
          {
            return std::make_shared<Square>(point);
          }}
      };

std::istream& operator>>(std::istream& in, std::shared_ptr<Shape>& shape)
{
  in >> std::ws;
  if(in.peek() == EOF)
  {
    in.setstate(std::ios_base::eofbit);
    return in;
  }
  std::string typeString;
  while((in.peek() != '(') && !isblank(in.peek()))
  {
    if(in.peek() == '\n')
    {
      in.setstate(std::ios_base::failbit);
      return in;
    }
    typeString += in.get();
  }

  Point point;
  in >> point;

  if(in.fail())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  if(constructors.find(typeString) != constructors.end())
  {
    shape = std::move(constructors.at(typeString)(point));
    return in;
  }
  in.setstate(std::ios_base::failbit);
  return in;
}

std::ostream& operator<<(std::ostream& out, const std::shared_ptr<Shape>& shape)
{
  shape->draw(out);
  return out;
}

void task2()
{
  std::vector<std::shared_ptr<Shape>>shapes(std::istream_iterator<std::shared_ptr<Shape>>(std::cin),
      std::istream_iterator<std::shared_ptr<Shape>>());

  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error in reading data in task2");
  }

  std::cout << "Original:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));

  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isMoreLeft, std::bind(&std::shared_ptr<Shape>::operator*,
      std::placeholders::_1), std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_2)));
  std::cout << "Left-Right:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));

  std::cout << "Right-Left:\n";
  std::copy(shapes.rbegin(), shapes.rend(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));

  std::sort(shapes.begin(), shapes.end(), std::bind(&Shape::isUpper, std::bind(&std::shared_ptr<Shape>::operator*,
      std::placeholders::_1), std::bind(&std::shared_ptr<Shape>::operator*, std::placeholders::_2)));
  std::cout << "Top-Bottom:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));

  std::cout << "Bottom-Top:\n";
  std::copy(shapes.rbegin(), shapes.rend(), std::ostream_iterator<std::shared_ptr<Shape>>(std::cout, "\n"));
}
