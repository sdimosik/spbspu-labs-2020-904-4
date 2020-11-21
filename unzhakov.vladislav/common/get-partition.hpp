#ifndef GET_PARTION_HPP
#define GET_PARTION_HPP

#include "matrix.hpp"
#include "shape.hpp"

namespace unzhakov
{
  Matrix getPartition(const Shape::SharedPtr *elem, size_t size);
}

#endif //GET_PARTION_HPP
