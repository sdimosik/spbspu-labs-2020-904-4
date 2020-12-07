#include "utilities.hpp"
#include <iostream>
int lovkacheva::square(int base)
{
  return base * base;
}


void lovkacheva::skipNonNewlineWs(std::istream &in)
{
  char next = in.peek();
  while (isspace(next))
  {
    if (next == '\n')
    {
      throw std::runtime_error("Invalid input: no newlines between data allowed");
    }
    in.get();
    next = in.peek();
  }
}