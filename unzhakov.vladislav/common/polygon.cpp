#include "polygon.hpp"
#include <cmath>
#include <algorithm>
#include <initializer_list>
#include <stdexcept>
#include <iostream>
#include "base-types.hpp"

unzhakov::Polygon::Polygon(const std::initializer_list<point_t> &newPoints)
{
  if (newPoints.size() < 3)
  {
    throw std::range_error("There should be 3 or more verticies");
  }
  size_ = newPoints.size();
  std::unique_ptr<point_t[]> temp(new point_t[size_]);
  int i = 0;

  for (std::initializer_list<point_t>::const_iterator point = newPoints.begin(); point != newPoints.end(); point++)
  {
    temp[i] = *point;
    i++;
  }
  points_.swap(temp);
  if (getArea() == 0)
  {
    throw std::invalid_argument("Polygon area should be > 0");
  }
}

unzhakov::point_t unzhakov::Polygon::operator[](std::size_t index) const
{
  if (index > size_)
  {
    throw std::out_of_range("Point does not exist");
  }
  return points_[index];
}

void unzhakov::Polygon::move(double dx, double dy)
{
  for (std::size_t i = 0; i < size_; i++)
  {
    points_[i].x += dx;
    points_[i].y += dy;
  }
}

void unzhakov::Polygon::move(const point_t &newCentre)
{
  point_t centre = getCenter();
  double dx = newCentre.x - centre.x;
  double dy = newCentre.y - centre.y;
  move(dx, dy);
}

void unzhakov::Polygon::scale(double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Coefficient should be > 0");
  }
  point_t centre = getCenter();
  double dx = 0;
  double dy = 0;
  for (std::size_t i = 0; i < size_; i++)
  {
    dx = (points_[i].x - centre.x) * coefficient;
    dy = (points_[i].y - centre.y) * coefficient;
    points_[i].x = centre.x + dx;
    points_[i].y = centre.y + dy;
  }
}

void unzhakov::Polygon::rotate(double angle)
{
  point_t temp_point = {0, 0};
  point_t centre = getCenter();
  angle = angle * M_PI / 180.0;
  for (std::size_t i = 0; i < size_; i++)
  {
    temp_point.x = points_[i].x - centre.x;
    temp_point.y = points_[i].y - centre.y;
    points_[i].x = temp_point.x * cos(angle) - temp_point.y * sin(angle) + centre.x;
    points_[i].y = temp_point.y * cos(angle) + temp_point.x * sin(angle) + centre.y;
  }
}

double unzhakov::Polygon::getArea() const
{
  double area = 0;
  for (std::size_t i = 0; i < size_ - 1; i++)
  {
    area += points_[i].x * points_[i + 1].y - points_[i].y * points_[i + 1].x;
  }
  area += points_[size_ - 1].x * points_[0].y - points_[size_ - 1].y * points_[0].x;
  return fabs(area) / 2.0;
}

unzhakov::rectangle_t unzhakov::Polygon::getFrameRect() const
{
  double min_x{points_[0].x};
  double max_x{points_[0].x};
  double min_y{points_[0].y};
  double max_y{points_[0].y};
  rectangle_t frame{0, 0, {0, 0}};
  for (std::size_t i = 1; i < size_; i++)
  {
    min_x = std::min(min_x, points_[i].x);
    min_y = std::min(min_y, points_[i].y);
    max_x = std::max(max_x, points_[i].x);
    max_y = std::max(max_y, points_[i].y);
  }
  frame.pos.x = min_x + (max_x - min_x) / 2.0;
  frame.pos.y = min_y + (max_y - min_y) / 2.0;
  frame.width = max_x - min_x;
  frame.height = max_y - min_y;
  return frame;
}

unzhakov::point_t unzhakov::Polygon::getCenter() const
{
  point_t centre = {0, 0};
  for (std::size_t i = 0; i < size_; i++)
  {
    centre.x += points_[i].x;
    centre.y += points_[i].y;
  }
  centre.x /= size_;
  centre.y /= size_;
  return centre;
}

void unzhakov::Polygon::printData() const
{
  std::cout << "Polygon\n";
  for (size_t i = 0; i < size_; i++)
  {
    std::cout << i + 1 << " point:" << "( " << points_[i].x << " ; " << points_[i].y << " )\n";
  }
}

void unzhakov::Polygon::printFrameRectangle() const
{
  std::cout << "Rectangular polygon frame: height = " << getFrameRect().height
    << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
    << ", " << getFrameRect().pos.y << "}\n";
}

void unzhakov::Polygon::printArea() const
{
  std::cout << "Area of a polygon = " << getArea() << '\n';
}
