#include "task_func.hpp"
#include <algorithm>

int count_vertices(Shapes& shapes)
{
  int count_of_vertices = 0;
  std::for_each(shapes.begin(), shapes.end(), [&](const Shape &shape)
  {
    count_of_vertices += shape.size();
  });
  return count_of_vertices;
}

int count_triangles(Shapes& shapes)
{
  return std::count_if(shapes.begin(), shapes.end(),
                       [](Shape& shape){return is_triangle(shape);});
}

int count_rectangles(Shapes& shapes)
{
  return std::count_if(shapes.begin(), shapes.end(),
                       [](Shape& shape){return is_rectangle(shape);});
}
int count_squares(Shapes& shapes)
{
  return std::count_if(shapes.begin(), shapes.end(),
                       [](Shape& shape){return is_square(shape);});
}

void delete_pentagons(Shapes& shapes)
{
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [&](const Shape &shape)
  {
    return shape.size() == 5;
  }), shapes.end());
}

std::vector<Point> create_point_vec(Shapes& shapes)
{
  std::vector<Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [](const Shape& shape){return shape.front();});
  return points;
}

