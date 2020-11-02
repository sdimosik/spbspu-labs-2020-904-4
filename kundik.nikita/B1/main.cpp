#include <stdexcept>
#include <iostream>
#include <cstring>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Incorrect number of arguments! Here must be from 1 to 3 arguments!\n";
      return 1;
    }

    int taskNumber = std::strtol(argv[1], nullptr, 10);
    bool isSortDirection = false;
    if (argc > 2)
    {
      isSortDirection = strcmp(argv[2], "ascending") == 0 || strcmp(argv[2], "descending") == 0;
    }
    switch (taskNumber)
    {
    case 1:
    {
      if (argc != 3)
      {
        std::cerr << "Incorrect number of arguments! First task must have 1 argument!\n";
        return 1;
      }
      if (!isSortDirection)
      {
        std::cerr << "Incorrect second argument! Sort direction must be ascending or descending!\n";
        return 1;
      }
      task::doFirstTask(argv[2]);
      break;
    }

    case 2:
    {
      if (argc != 3)
      {
        std::cerr << "Incorrect number of arguments! Second task must have 1 argument!\n";
        return 1;
      }
      task::doSecondTask(argv[2]);
      break;
    }

    case 3:
    {
      if (argc != 2)
      {
        std::cerr << "Incorrect number of arguments! Third task must have no arguments!\n";
        return 1;
      }
      task::doThirdTask();
      break;
    }

    case 4:
    {
      if (argc != 4)
      {
        std::cerr << "Incorrect number of arguments! Fourth task must have 2 arguments!\n";
        return 1;
      }
      if (!isSortDirection)
      {
        std::cerr << "Incorrect second argument! Sort direction must be ascending or descending!\n";
        return 1;
      }
      size_t size = std::strtol(argv[3], nullptr, 10);
      if (size <= 0)
      {
        std::cerr << "Incorrect third argument! Array size must be positive!\n";
        return 1;
      }
      task::doFourthTask(argv[2], size);
      break;
    }

    default:
    {
      std::cerr << "Incorrect task number! Task number must be from 1 to 4!\n";
      return 1;
    }
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return -1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!\n";
    return -2;
  }
  return 0;
}
