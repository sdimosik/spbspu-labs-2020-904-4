#include "blanks.hpp"

std::istream& blank(std::istream& in)
{
  while (isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}
