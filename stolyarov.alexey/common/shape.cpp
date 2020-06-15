#include "shape.hpp"

namespace stolyarov
{
  Shape::Shape() noexcept :
    pos_(point_t{0, 0})
  {}

  Shape::Shape(const point_t& pos) noexcept :
    pos_(pos)
  {
  }
}
