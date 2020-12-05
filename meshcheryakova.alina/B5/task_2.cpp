#include <iterator>
#include <algorithm>
#include "shape.hpp"
#include "task_func.hpp"

void task_2()
{
  Shapes shapes((std::istream_iterator<Shape>(std::cin)), std::istream_iterator<Shape>());

  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::ios_base::failure(" fail in reading stream ! \n");
  }

  std::cout << "Vertices: " << count_vertices(shapes) << '\n';
  std::cout << "Triangles: " << count_triangles(shapes) << '\n';
  std::cout << "Squares: " << count_squares(shapes) << '\n';
  std::cout << "Rectangles: " << count_rectangles(shapes) << '\n';
  delete_pentagons(shapes);
  std::vector<Point> points = create_point_vec(shapes);
  std::cout << "Points: ";
  print_points(points, std::cout);
  std::cout << '\n';
  std::sort(shapes.begin(), shapes.end(), [](const Shape& first, const Shape& second)
  {
    return compare(first, second);
  });
  std::cout << "Shapes: " << '\n';
  print_shapes(shapes, std::cout);

}
