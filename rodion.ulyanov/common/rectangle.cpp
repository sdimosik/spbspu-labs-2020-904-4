
#include "rectangle.hpp"
namespace rodion
{
  Rectangle::Rectangle(const rectangle_t &rectangle) :
      rectangle(rectangle) {
    if (rectangle.height <= 0.0) {
      std::string exc = "Invalid height input" + std::to_string(rectangle.height);
      throw std::invalid_argument(exc);
    }

    if (rectangle.width <= 0.0) {
      std::string exc = "Invalid width input" + std::to_string(rectangle.width);
      throw std::invalid_argument(exc);
    }
  }

  double Rectangle::getArea() const {
    return rectangle.height * rectangle.width;
  }

  rectangle_t Rectangle::getFrameRect() const
  {
    return rectangle;
  }

  void Rectangle::show() const
  {
    std::cout << "Rectangle's width is :" << rectangle.width << std::endl;
    std::cout << "Rectangle's height is :" << rectangle.height << std::endl;
    std::cout << "Rectangle's center is: (" << rectangle.pos.x << "," << rectangle.pos.y << ")" << std::endl;
  }

  void Rectangle::move(const point_t &x)
  {
    rectangle.pos = x;
  }

  void Rectangle::move(const double x, const double y)
  {
    rectangle.pos.x = x;
    rectangle.pos.y = y;
  }

  void Rectangle::scale(double value)
  {
    if (value <= 0) {
      throw std::invalid_argument(std::string("Value must be positive, value = "
                                              + std::to_string(value)));
    }
    rectangle.width *= value;
    rectangle.height *= value;

  }
};
