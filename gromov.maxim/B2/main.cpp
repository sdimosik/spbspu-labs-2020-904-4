#include <iostream>
#include <stdexcept>
#include "first.hpp"
#include "second.hpp"

int main(int argc, char * argv[])
{
  try
  {
    if(argc != 2)
    {
      throw std::invalid_argument("Invalid count of argc!");
    }

    for(const auto & ch : std::string(argv[1]))
    {
      if (ch < '0' || ch > '9')
      {
        throw std::invalid_argument("Invalid task number");
      }
    }
    
    int part = atoi(argv[1]);

    if(part == 1)
    {
      firstTask();
    } else if (part == 2)
    {
      secondTask();
    }
    else
    {
      throw std::invalid_argument("Invalid taks number!");
    }
    return 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown problem\n";
    return 2;
  }
}
