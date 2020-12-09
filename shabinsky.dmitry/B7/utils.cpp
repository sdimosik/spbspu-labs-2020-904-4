#include "utils.hpp"

std::istream &utils::space(std::istream &in)
{
  while (!in.eof() && std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}
