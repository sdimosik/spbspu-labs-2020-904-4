#ifndef MANIPULATOR_HPP
#define MANIPULATOR_HPP

#include <cctype>
#include <istream>

std::istream &space(std::istream &in)
{
  while (!in.eof() && std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}

#endif
