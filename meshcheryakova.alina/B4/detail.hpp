#ifndef B4_DETAIL_HPP
#define B4_DETAIL_HPP
#include <iostream>

std::istream& blank(std::istream& in)
{
  if(in.peek() == '\n')
  {
    in.clear();
    in.setstate(std::ios_base::failbit);
    return in;
  }

  while(isspace(in.peek()))
  {
    in.ignore(1);
    if(in.peek() == '\n')
    {
      in.clear();
      in.setstate(std::ios_base::failbit);
      return in;
    }
  }
  return in;
}

#endif //B4_DETAIL_HPP
