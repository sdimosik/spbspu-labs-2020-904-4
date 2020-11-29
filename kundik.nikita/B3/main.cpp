#include <iostream>
#include <stdexcept>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid amount of input parameters");
    }
    int taskNumber = std::atoi(argv[1]);
    if (taskNumber == 1)
    {
      task1();
    }
    else if (taskNumber == 2)
    {
      task2();
    }
    else
    {
      throw std::invalid_argument("Invalid task number");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 2;
  }
  return 0;
}
