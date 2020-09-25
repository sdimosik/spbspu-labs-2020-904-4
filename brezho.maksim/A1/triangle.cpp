#include "triangle.hpp"
#include <stdexcept>
#include <cmath>

Triangle::Triangle(const point_t& pos, double base, double sideLeft, double sideRight) :
  triangle_ {base, sideLeft, sideRight, pos}
{
  if (base <= 0)
  {
    throw std::invalid_argument("The base of the triangle must be a positive number.");
  }
  if (sideLeft <= 0)
  {
    throw std::invalid_argument("The left side of the triangle must be a positive number.");
  }
  if (sideRight <= 0)
  {
    throw std::invalid_argument("The right side of the triangle must be a positive number.");
  }
  if (base + sideLeft <= sideRight || base + sideRight <= sideLeft || sideRight + sideLeft <= base)
  {
    throw std::invalid_argument("The sum of the two sides of the triangle must be greater than the third side.");
  }
}

void Triangle::move(const point_t& pos)
{
  triangle_.pos = pos;
}

void Triangle::move(double x, double y)
{
  triangle_.pos.x += x;
  triangle_.pos.y += y;
}

rectangle_t Triangle::getFrameRect() const
{
  double width = 0, height = 2 * getArea() / triangle_.base;
  if (pow(triangle_.base, 2) + pow(triangle_.sideRight, 2) - pow(triangle_.sideLeft, 2) < 0)
  {
    width = sqrt(pow(triangle_.sideLeft, 2) - pow(height, 2));
  }
  else if (pow(triangle_.base, 2) + pow(triangle_.sideLeft, 2) - pow(triangle_.sideRight, 2) < 0)
  {
    width = sqrt(pow(triangle_.sideRight, 2) - pow(height, 2));
  }
  else
  {
    width = triangle_.base;
  }
  point_t temp;
  temp.x = width / 2;
  temp.y = height / 2;
  return rectangle_t{ width, height, temp };
}

double Triangle::getBase() const
{
  return triangle_.base;
}

double Triangle::getSideLeft() const
{
  return triangle_.sideLeft;
}

double Triangle::getSideRight() const
{
  return triangle_.sideRight;
}

void Triangle::setBase(double base)
{
  if (base <= 0)
  {
    throw std::invalid_argument("The base of the triangle must be a positive number.");
  }
  if (base + triangle_.sideLeft <= triangle_.sideRight || base + triangle_.sideRight <= triangle_.sideLeft || triangle_.sideRight + triangle_.sideLeft <= base)
  {
    throw std::invalid_argument("The sum of the two sides of the triangle must be greater than the third side.");
  }
  triangle_.base = base;
}

void Triangle::setSideLeft(double sideLeft)
{
  if (sideLeft <= 0)
  {
    throw std::invalid_argument("The left side of the triangle must be a positive number.");
  }
  if (sideLeft + triangle_.base <= triangle_.sideRight || sideLeft + triangle_.sideRight <= triangle_.base || triangle_.sideRight + triangle_.base <= sideLeft)
  {
    throw std::invalid_argument("The sum of the two sides of the triangle must be greater than the third side.");
  }
  triangle_.sideLeft = sideLeft;
}

void Triangle::setSideRight(double sideRight)
{
  if (sideRight <= 0)
  {
    throw std::invalid_argument("The right side of the triangle must be a positive number.");
  }
  if (sideRight + triangle_.base <= triangle_.sideLeft || sideRight + triangle_.sideLeft <= triangle_.base || triangle_.sideLeft + triangle_.base <= sideRight)
  {
    throw std::invalid_argument("The sum of the two sides of the triangle must be greater than the third side.");
  }
  triangle_.sideRight = sideRight;
}

point_t Triangle::getPosition() const
{
  return triangle_.pos;
}

double Triangle::getArea() const
{
  double p = (triangle_.base + triangle_.sideLeft + triangle_.sideRight) / 2;
  double area = sqrt(p * (p - triangle_.base) * (p - triangle_.sideLeft) * (p - triangle_.sideRight));
  return area;
}
