#include "shape.hpp"
#include<iostream>
namespace sviridov
{
  std::ostream& operator<<(std::ostream& out, const Shape& out_shape)
  {
    out_shape.printInform(out);
    return out;
  }
}
