#include <iostream>
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Invalid number of arguments");
    }
    int taskNumber = atoi(argv[1]);

    switch (taskNumber)
    {
    case 1:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid number of arguments");
      }
      task1(argv[2]);
      break;

    case 2:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid number of arguments");
      }
      task2(argv[2]);
      break;

    case 3:
      if (argc != 2)
      {
        throw std::invalid_argument("Invalid number of arguments");
      }
      task3();
      break;
      
    case 4:
      if (argc != 4)
      {
        throw std::invalid_argument("Invalid number of arguments");
      }
      task4(argv[2], atoi(argv[3]));
      break;

    default:
      throw std::invalid_argument("Invalid task number");
      break;
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return -1;
  }
  return 0;
}
