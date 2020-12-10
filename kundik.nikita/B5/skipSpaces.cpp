#include "skipSpaces.hpp"
#include <cctype>

std::istream& skipSpaces(std::istream& in)
{
  while (std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}
