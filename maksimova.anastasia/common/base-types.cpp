#include "base-types.hpp"

namespace maksimova
{
  void rectangle_t::print() const
  {
    std::cout << "Width = " << width << ", " << "Height = " << height
        << ", " << "Position (" << pos.x << ", " << pos.y << ")\n";
  }
}
