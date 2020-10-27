#include<iostream>

std::string input_line_with_spaces(std::string &line)
{
  getline(std::cin, line);
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
