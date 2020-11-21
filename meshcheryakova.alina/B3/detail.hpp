#ifndef B3_DETAIL_HPP
#define B3_DETAIL_HPP

#include <iostream>
std::string input_line_with_spaces(std::istream& in, std::string &line)
{
  getline(in, line);
  auto iter_end = line.begin();
  for(; iter_end != line.end();)
  {
    if(isspace(*iter_end))
    {
      iter_end = line.erase(iter_end);
    }
    else
    {
      break;
    }
  }
  return line;
}

#endif //B3_DETAIL_HPP
