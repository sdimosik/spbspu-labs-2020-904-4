#include "circle.hpp"
#include <iostream>
#include <string>
#include <stdexcept>
#include <cmath>

Circle::Circle(double radius, const point_t& pos) : 
  Shape(pos),
  radius_(radius)
  
{
  if (radius <= 0)
  {
    throw std::invalid_argument("Incorrect argument radius was given: " + std::to_string(radius));
  }
}

void Circle::move(double x, double y)
{
  pos_.x += x;
  pos_.y += y;
}

void Circle::move(const point_t& pos)
{
  pos_ = pos;
}

double Circle::getArea() const
{
  return (M_PI * radius_ * radius_);
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t({ 2 * radius_,2 * radius_,pos_ });
}

void Circle::printInf()
{
  std::cout << "Circle information" << std::endl
      << "Center's location:" << std::endl
      << "x: " << pos_.x << std::endl << "y: " << pos_.y << std::endl
      << "Parameters of the circle:" << std::endl
      << "radius: " << radius_ << std::endl
      << "Area of the circle: " << getArea() << std::endl << std::endl;
}

void Circle::printFrameInf()
{
  std::cout << "Frame information" << std::endl
      << "Center's location:" << std::endl
      << "x: " << getFrameRect().pos.x << std::endl << "y: " << getFrameRect().pos.y << std::endl
      << "Parameters of the frame:" << std::endl
      << "height: " << getFrameRect().height << std::endl << "widht: " << getFrameRect().width << std::endl << std::endl;
}
