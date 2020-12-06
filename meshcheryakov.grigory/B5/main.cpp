#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid count of args!\n");
    }
    int taskNumber = std::stoi(argv[1]);
    switch (taskNumber)
    {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        throw std::invalid_argument("Invalid task number!\n");
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return 2;
  }

  return 0;
}
