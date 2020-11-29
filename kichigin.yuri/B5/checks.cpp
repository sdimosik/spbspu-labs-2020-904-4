#include "checks.hpp"
#include <cmath>


bool isTriangle(const Shape& shape)
{
  return shape.points.size() == Shape::TRIANGLE_VERTICES;
}

bool isSquare(const Shape& shape)
{
  if (shape.points.size() == Shape::QUADRANGLE_VERTICES && isRectangle(shape))
  {
    return (pow(shape.points[1].x - shape.points[0].x, 2) + pow(shape.points[1].y - shape.points[0].y, 2)
        == pow(shape.points[3].x - shape.points[0].x, 2) + pow(shape.points[3].y - shape.points[0].y, 2));
  }
  return false;
}

bool isRectangle(const Shape& shape)
{
  if (shape.points.size() == Shape::QUADRANGLE_VERTICES)
  {
    using Vector2d = Point;
    Vector2d ab = { shape.points[1].x - shape.points[0].x, shape.points[1].y - shape.points[0].y };
    Vector2d bc = { shape.points[2].x - shape.points[1].x, shape.points[2].y - shape.points[1].y };
    Vector2d cd = { shape.points[3].x - shape.points[2].x, shape.points[3].y - shape.points[2].y };
    Vector2d ad = { shape.points[3].x - shape.points[0].x, shape.points[3].y - shape.points[0].y };
    return ((ab.x * cd.y == ab.y * cd.x) && (ab.x * bc.x + ab.y * bc.y == 0) && (ab.x * ad.x + ab.y * ad.y == 0));
  }
  return false;
}

bool isPentagon(const Shape& shape)
{
  return shape.points.size() == Shape::PENTAGON_VERTICES;
}
