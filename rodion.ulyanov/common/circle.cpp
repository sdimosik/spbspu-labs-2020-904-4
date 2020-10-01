#include "circle.hpp"
#include <cmath>
namespace rodion
{
  Circle::Circle(const double &radius, const point_t &centre):
    radius(radius),
    centre(centre)
  {
    if (radius <= 0.0)
    {
      std::string exc = "invalid radius input" + std::to_string(radius);
      throw std::invalid_argument(exc);
    }
  }

  void Circle::move(const point_t &x)
  {
    centre = x;
  }

  void Circle::move(const double x, const double y)
  {
    centre.x += x;
    centre.y += y;
  }

  rectangle_t Circle::getFrameRect() const
  {
    return rectangle_t{radius, radius, centre};
  }

  double Circle::getArea() const
  {
    return M_PI * (radius * radius);
  }

  void Circle::show() const
  {
    std::cout << "Circle's center is: (" << centre.x << "," << centre.y << ")" << '\n';
    std::cout << "Circle's radius is: " << radius << '\n';
  }

  void Circle::scale(double value)
  {
    if (value <= 0)
    {
      throw std::invalid_argument(std::string("Value must be positive, value = " + std::to_string (value)));
    }
    radius *= value;
  }
}

