#include <iostream>
#include <vector>
#include <cstdlib>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of arguments\n");
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
        throw std::invalid_argument("Task number must be between 1 and 2!\n");
    }
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Error occurred!" << std::endl;
    return -1;
  }

  return 0;
}

