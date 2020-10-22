#include <iostream>
#include <stdexcept>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Error: wrong amount of argc entered!");
    }

    int taskNumber = atoi(argv[1]);

    switch(taskNumber)
    {
      case 1:
      {
        task1();
        break;
      }
      case 2:
      {
        task2();
        break;
      }
      default:
      {
        throw std::invalid_argument("Error: wrong task number entered!");
      }
    }
  }
  catch (const std::exception& except)
  {
    std::cerr << except.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return 1;
  }

  return 0;
}
