#include <iostream>
#include <vector>
#include <cstdlib>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Invalid number of arguments\n");
    }
    int taskNumber = std::atoi(argv[1]);
    switch (taskNumber)
    {
      case 1:
        if (argc != 3)
        {
          throw std::invalid_argument("Invalid number of arguments!\n");
        }
        task1(argv[2]);
        break;
      case 2:
        if (argc != 3)
        {
          throw std::invalid_argument("Invalid number of arguments!\n");
        }
        task2(argv[2]);
        break;
      case 3:
        if (argc != 2)
        {
          throw std::invalid_argument("Invalid number of arguments!\n");
        }
        task3();
        break;
      case 4:
        if (argc != 4)
        {
          throw std::invalid_argument("Invalid number of arguments!\n");
        }
        task4(argv[2], std::atoi(argv[3]));
        break;
      default:
        throw std::invalid_argument("Task number must be between 1 and 4!\n");
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

