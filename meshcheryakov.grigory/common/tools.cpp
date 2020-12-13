#include "tools.hpp"

std::istream &skipSpace(std::istream &in)
{
  while (std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}
