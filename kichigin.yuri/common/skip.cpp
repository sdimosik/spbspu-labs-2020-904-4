#include "skip.hpp"
#include <iostream>
#include <cctype>

std::istream& skipBlanks(std::istream& in)
{
  while (std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}
