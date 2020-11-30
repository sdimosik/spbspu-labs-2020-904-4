#include "data-struct.hpp"
#include <iostream>

std::ostream& lovkacheva::operator<<(std::ostream &out, const lovkacheva::DataStruct &rhs)
{
  out << rhs.key1 << ',' << rhs.key2 << ',' << rhs.str;
  return out;
}
