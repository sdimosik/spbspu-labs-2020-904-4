#include <stdexcept>
#include <iostream>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Incorrect number of arguments! Here must be 1 argument!\n";
      return 1;
    }

    int taskNumber = std::strtol(argv[1], nullptr, 10);
    switch (taskNumber)
    {
      case 1:
      {
        task::doFirstTask();
        break;
      }

      case 2:
      {
        task::doSecondTask();
        break;
      }

      default:
      {
        std::cerr << "Incorrect task number! Task number must be 1 or 2!\n";
        return 1;
      }
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return 1;
  }
  return 0;
}
