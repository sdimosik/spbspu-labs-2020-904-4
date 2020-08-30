

#include "circle.hpp"
#include "math.h"

Circle::Circle(const double &radius, const point_t &centre) :
  radius(radius),
  centre(centre)
{
  if (radius <=0.0)
  {
      std::string exc = "Invalid radius input" + std::to_string(radius);
      throw std::invalid_argument(exc);
  }
}

void Circle::move(const point_t &x)
{
  centre = x;
}

void Circle::move(const double x, const double y)
{
  centre.x = x;
  centre.y = y;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t {radius,radius,centre};
}

double Circle::getArea() const
{
  return M_PI * (radius * radius);
}

void Circle::show() const
{
  std::cout << "Circle's center is: (" << centre.x << "," << centre.y << ")" <<  '\n';
  std::cout << "Circles' radius is: " << radius << '\n';
}
