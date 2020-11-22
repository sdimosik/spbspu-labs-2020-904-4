#include "rectangle.hpp"

#include <iostream>
#include <stdexcept>
#include <string>
#include <math.h>

unzhakov::Rectangle::Rectangle(double width, double height, const point_t& centre, double angle) :
  vertex_{{centre.x - width / 2.0, centre.y - height / 2.0}, {centre.x + width / 2.0, centre.y - height / 2.0},
          {centre.x + width / 2.0, centre.y + height / 2.0}, {centre.x - width / 2.0, centre.y + height / 2.0}}

{
  if (width <= 0.0)
  {
    throw std::invalid_argument("Invalid width value in circle = " + std::to_string(width) + '\n');
  }
  if (height <= 0.0)
  {
    throw std::invalid_argument("Invalid radius value in circle = " + std::to_string(height) + '\n');
  }
  rotate(angle);
}

unzhakov::rectangle_t unzhakov::Rectangle::getFrameRect() const
{
  double maxLeft = vertex_[0].x;
  double maxRight = vertex_[0].x;
  double maxDown = vertex_[0].y;
  double maxUp = vertex_[0].y;
  for (size_t i = 1; i < sizeof(vertex_) / sizeof(*vertex_); i++) {
    maxLeft = std::min(maxLeft, vertex_[i].x);
    maxRight = std::max(maxRight, vertex_[i].x);
    maxDown = std::min(maxDown, vertex_[i].y);
    maxUp = std::max(maxUp, vertex_[i].y);
  }
  const double width = maxRight - maxLeft;
  const double height = maxUp - maxDown;
  return rectangle_t{width, height, {(maxLeft + maxRight) / 2, (maxDown + maxUp) / 2}};

}

double unzhakov::Rectangle::getArea() const
{
  return getWidth() * getHeight();
}

double unzhakov::Rectangle::getHeight() const
{
  return sqrt((vertex_[3].y - vertex_[0].y) * (vertex_[3].y - vertex_[0].y)
              + (vertex_[3].x - vertex_[0].x) * (vertex_[3].x - vertex_[0].x));
}

double unzhakov::Rectangle::getWidth() const
{
  return sqrt((vertex_[1].x - vertex_[0].x) * (vertex_[1].x - vertex_[0].x)
              + (vertex_[1].y - vertex_[0].y) * (vertex_[1].y - vertex_[0].y));
}

unzhakov::point_t unzhakov::Rectangle::getCenter() const
{
  return {(vertex_[0].x + vertex_[2].x) / 2, (vertex_[0].y + vertex_[2].y) / 2};
}


void unzhakov::Rectangle::move(double x, double y)
{
  for(size_t i = 0; i < 4; i++)
  {
    vertex_[i].x += x;
    vertex_[i].y += y;
  }
}

void unzhakov::Rectangle::move(const point_t &center)
{
  const unzhakov::point_t centre = getCenter();
  move(center.x - centre.x, center.y - centre.y);

}

void unzhakov::Rectangle::scale(const double coefficient)
{
  if (coefficient <= 0)
  {
    throw std::invalid_argument("Invalid coefficient in rectangle = " + std::to_string(coefficient) + '\n');
  }
  unzhakov::point_t centre = getCenter();
  for(size_t i = 0; i < sizeof(vertex_) / sizeof(*vertex_); i++)
  {
    const double distanceX = (vertex_[i].x - centre.x) * coefficient;
    const double distanceY = (vertex_[i].y - centre.y) * coefficient;
    vertex_[i] = {centre.x + distanceX, centre.y + distanceY};
  }
}

void unzhakov::Rectangle::rotate(double angle)
{
  const double a = angle / 180 * M_PI;
  const double sinAngle = sin(a);
  const double cosAngle = cos(a);
  unzhakov::point_t centre = getCenter();
  for (size_t i = 0; i < sizeof(vertex_) / sizeof(*vertex_); i++)
  {
    const double posX = (vertex_[i].x - centre.x) * cosAngle - (vertex_[i].y - centre.y) * sinAngle + centre.x;
    const double posY = (vertex_[i].x - centre.x) * sinAngle + (vertex_[i].y - centre.y) * cosAngle + centre.y;
    vertex_[i] = {posX, posY};
  }
}

void unzhakov::Rectangle::printData() const
{
  const unzhakov::point_t center = getCenter();
  std::cout << "Rectangle width: " << getWidth() << '\n'
      << "Rectangle height: " << getHeight() << '\n'
      << "Rectangle center: {" << center.x << ", " << center.y << "}\n";
}

void unzhakov::Rectangle::printFrameRectangle() const
{
  std::cout << "Rectangle frame for rectangle: height = " << getFrameRect().height
      << ", width = " << getFrameRect().width << ", center = {" << getFrameRect().pos.x
      << ", " << getFrameRect().pos.y << "}\n";
}

void unzhakov::Rectangle::printArea() const
{
  std::cout << "Rectangle area = " << getArea() << '\n';
}
