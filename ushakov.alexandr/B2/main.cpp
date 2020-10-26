#include <iostream>
#include <stdexcept>
#include <cctype>
#include "first.hpp"
#include "second.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid count of argc!");
    }

    for (const char& ch : std::string(argv[1]))
    {
      if (!isdigit(ch))
      {
        throw std::invalid_argument("Invalid task number");
      }
    }

    char *p;
    long part = strtol(argv[1], &p, 10);
    if (*p != '\0')
    {
      throw std::invalid_argument("Invalid task number");
    }

    switch (part)
    {
      case 1:
      {
        firstTask();
        break;
      }
      case 2:
      {
        secondTask();
        break;
      }
      default:
      {
        throw std::invalid_argument("Invalid task number");
      }
    }

    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << std::endl;

    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem" << std::endl;

    return 2;
  }
}
