#include "algorithm.hpp"
#include <algorithm>
#include <vector>

void deletePentagon(vectorShapes &shapes)
{
  shapes.erase(std::remove_if(shapes.begin(), shapes.end(), [&](const Shape &shape)
  {
    return shape.points.size() == PENTAGON_VERT;
  }), shapes.end());
}

std::vector<point_t> extractPointsFromShapes(const vectorShapes &shapes)
{
  std::vector<point_t> points;
  points.reserve(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(), [] (const Shape &shape)
  {
    return shape.points.front();
  });
  return points;
}
