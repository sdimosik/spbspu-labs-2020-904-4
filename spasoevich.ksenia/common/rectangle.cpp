#include "rectangle.hpp"
#include <stdexcept>

namespace spasoevich
{
  Rectangle::Rectangle(const point_t& center, const double width, const double height) :
    rect({ center, width, height })
  {
    if (width <= 0 || height <= 0)
    {
      throw std::invalid_argument(" Dimensions can't be negaitve or equal to zero. ");
    }
  }

  double Rectangle::getArea() const noexcept
  {
    return (rect.width * rect.height);
  }

  rectangle_t Rectangle::getFrameRect() const noexcept
  {
    return rect;
  }

  void Rectangle::move(const double dx, const double dy) noexcept
  {
    rect.pos.x += dx;
    rect.pos.y += dy;
  }

  void Rectangle::move(const point_t& pt) noexcept
  {
    rect.pos = pt;
  }

  void Rectangle::scale(const double coefficient)
  {
    if (coefficient <= 0)
    {
      throw std::invalid_argument("Coefficent can't be less or equal to zero. ");
    }
    else
    {
      rect.width = rect.width * coefficient;
      rect.height = rect.height * coefficient;
    }
  }
}
