#include "manipulator.hpp"
#include <cctype>

std::istream& manipulator(std::istream& in)
{
  while(std::isblank(in.peek()))
  {
    in.get();
  }
  return in;
}
