#include <stdexcept>
#include <iostream>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid count of arguments");
    }
    int taskNumber = std::atoi(argv[1]);
    switch (taskNumber)
    {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    default:
      throw std::invalid_argument("Invalid argument number");
    }
  }
  catch (std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return 2;
  }
  return 0;
}
