#include <iostream>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Invalid amount of input parameters\n");
    }

    int tasks = std::stoi(argv[1]);

    if (tasks < 1 || tasks > 4)
    {
      throw std::invalid_argument(" wrong number of task\n");
    }

    switch (tasks)
    {
      case 1:
        if (argc != 3)
        {
          throw std::invalid_argument("Wrong count of arguments!\n");
        }
        task1(argv[2]);
        break;
      case 2:
        if (argc != 3)
        {
          throw std::invalid_argument("Wrong count of arguments!\n");
        }
        task2(argv[2]);
        break;
      case 3:
        if (argc != 2)
        {
          throw std::invalid_argument("Wrong count of arguments!\n");
        }
        task3();
        break;
      case 4:
        if (argc != 4)
        {
          throw std::invalid_argument("Wrong count of arguments!\n");
        }
        task4(argv[2], std::stoi(argv[3]));
        break;
      default:
        throw std::invalid_argument("Wrong number of task!\n");
    }
  }
  catch (const std::exception &e)
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
