#include <functional>
#include "shape.hpp"
#include "statsObject.hpp"

void task2()
{
  std::vector<Shape> container{std::istream_iterator<Shape>(std::cin), std::istream_iterator<Shape>()};
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Fail while reading!\n");
  }

  StatsObject statsObject;
  std::for_each(container.begin(), container.end(), std::ref(statsObject));

  container.erase(std::remove_if(container.begin(), container.end(), [](const Shape &shape)
  {
    return shape.type == Shape::ShapeType::PENTAGON;
  }), container.end());

  std::vector<Point> points(container.size());
  std::transform(container.begin(), container.end(), points.begin(), [](const Shape &shape)
  {
    return shape.points.front();
  });

  std::sort(container.begin(), container.end());

  std::cout << statsObject;

  std::cout << "Points: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(std::cout));

  std::cout << std::endl << "Shapes:" << std::endl;
  std::copy(container.begin(), container.end(), std::ostream_iterator<Shape>(std::cout));
}
