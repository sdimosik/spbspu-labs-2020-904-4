#include "polygon.hpp"

#include <cmath>
#include <iostream>

const double ACCURACY = 0.00001;
const int FULL_CIRCLE = 180;

ushakov::Polygon::Polygon(const std::initializer_list<point_t>& points) :
  numberOfPoints_(points.size()),
  points_(std::make_unique<point_t[]>(points.size()))
{
  if (points.size() < 3)
  {
    throw std::invalid_argument("Polygon constructor error: can't build polygon with less than 3 points (given "
          + std::to_string(points.size()) + ')');
  }

  std::copy(points.begin(), points.end(), points_.get());

  if (!isConvex())
  {
    throw std::invalid_argument("Polygon constructor error: polygon is non-convex");
  }

  if (getArea() < ACCURACY)
  {
    throw std::invalid_argument("Polygon constructor error: polygon must have positive area("
          + std::to_string(getArea()) + ')');
  }
}

void ushakov::Polygon::move(const point_t& newPosition) noexcept
{
  const point_t position = getPosition();

  const double xAxis = newPosition.x - position.x;
  const double yAxis = newPosition.y - position.y;

  move(xAxis, yAxis);
}

void ushakov::Polygon::move(double xAxis, double yAxis) noexcept
{
  for (size_t i = 0; i < numberOfPoints_; i++)
  {
    points_[i].x += xAxis;
    points_[i].y += yAxis;
  }
}

void ushakov::Polygon::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Polyhon scale error: Invalid coefficient of scale, it must be positive("
          + std::to_string(coefficient) + ')');
  }

  const point_t position = getPosition();

  for (size_t i = 0; i < numberOfPoints_; i++)
  {
    points_[i].x = position.x + (position.x - points_[i].x) * coefficient;
    points_[i].y = position.y + (position.y - points_[i].y) * coefficient;
  }
}

void ushakov::Polygon::rotate(double angle) noexcept
{
  const double angleInRadians = angle * M_PI / FULL_CIRCLE;

  const point_t position = getPosition();

  for (size_t i = 0; i < numberOfPoints_; i++)
  {
    const double previousX = points_[i].x;

    points_[i].x = position.x + (points_[i].x - position.x) * std::cos(angleInRadians)
        - (points_[i].y - position.y) * std::sin(angleInRadians);

    points_[i].y = position.y + (points_[i].y - position.y) * std::cos(angleInRadians)
        + (previousX - position.x) * std::sin(angleInRadians);
  }
}

double ushakov::Polygon::getArea() const noexcept
{
  double area = 0;

  for (size_t i = 0; i < numberOfPoints_ - 1; i++)
  {
    area += points_[i].x * points_[i + 1].y - points_[i].y * points_[i + 1].x;
  }

  area += points_[numberOfPoints_ - 1].x * points_[0].y - points_[numberOfPoints_ - 1].y * points_[0].x;

  return std::abs(area / 2);
}

ushakov::rectangle_t ushakov::Polygon::getFrameRect() const noexcept
{
  double xMin = points_[0].x;
  double xMax = points_[0].x;
  double yMin = points_[0].y;
  double yMax = points_[0].y;

  for (size_t i = 1; i < numberOfPoints_; i++)
  {
    xMin = std::min(xMin, points_[i].x);
    yMin = std::min(yMin, points_[i].y);
    xMax = std::max(xMax, points_[i].x);
    yMax = std::max(yMax, points_[i].y);
  }

  return rectangle_t{(xMax - xMin), (yMax - yMin), {(xMin + (xMax - xMin) / 2), (yMin
        + (yMax - yMin) / 2)}};
}

ushakov::point_t ushakov::Polygon::getPosition() const noexcept
{
  double x = 0;
  double y = 0;

  for (size_t i = 0; i < numberOfPoints_; i++)
  {
    x += points_[i].x;
    y += points_[i].y;
  }

  return point_t{x / static_cast<double>(numberOfPoints_), y / static_cast<double>(numberOfPoints_)};
}

bool ushakov::Polygon::isConvex() const
{
  double vectorProduct1 = (points_[0].x - points_[numberOfPoints_ - 1].x) * (points_[1].y - points_[0].y)
      - (points_[1].x - points_[0].x) * (points_[0].y - points_[numberOfPoints_ - 1].y);
  double vectorProduct2 = 0;

  for (size_t i = 0; i < numberOfPoints_ - 2; i++)
  {
    vectorProduct2 = (points_[i + 1].x - points_[i].x) * (points_[i + 2].y - points_[i + 1].y)
        - (points_[i + 2].x - points_[i + 1].x) * (points_[i + 1].y - points_[i].y);

    if (vectorProduct1 * vectorProduct2 >= 0)
    {
      vectorProduct1 = vectorProduct2;
    }
    else
    {
      return false;
    }
  }

  vectorProduct2 = (points_[numberOfPoints_ - 1].x - points_[numberOfPoints_ - 2].x)
      * (points_[0].y - points_[numberOfPoints_ - 1].y) - (points_[0].x - points_[numberOfPoints_ - 1].x)
      * (points_[numberOfPoints_ - 1].y - points_[numberOfPoints_ - 2].y);

  return (vectorProduct1 * vectorProduct2 >= 0);
}

void ushakov::Polygon::print() const noexcept
{
  std::cout << "Polygon " << std::endl;
  std::cout << "  vertexes:" << std::endl;

  for (size_t i = 0; i < numberOfPoints_; i++)
  {
    std::cout << "    " << i + 1 << ": x = " << points_[i].x << ", y = " << points_[i].y << std::endl;
  }

  std::cout << "  area: " << getArea() << std::endl;
}

void ushakov::Polygon::printFrameRectangle() const noexcept
{
  const rectangle_t rectangle = getFrameRect();

  std::cout << "Frame rectangle for this shape:" << std::endl;
  std::cout << "  height = " << rectangle.height << ",  width = " << rectangle.width << std::endl;
  std::cout << "  position: x = " << rectangle.pos.x << ", y = " << rectangle.pos.y << std::endl;
}
