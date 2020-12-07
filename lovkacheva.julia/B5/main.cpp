#include <stdexcept>
#include <iostream>
#include <cstring>
#include "parts.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of arguments\n");
    }
    if (strlen(argv[1]) > 1 || (argv[1][0] != '2' && argv[1][0] != '1'))
    {
      throw std::invalid_argument("Invalid task number, must be 1/2.");
    }
    int part = atoi(argv[1]);
    if (part == 1)
    {
      lovkacheva::partOne();
    }
    else
    {
      lovkacheva::partTwo();
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return 2;
  }
  return 0;
}
