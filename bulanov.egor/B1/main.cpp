#include <iostream>
#include "tasks.hpp"


int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Error: entered incorrect count of arguments\n");
    }
    int data = std::stoi(argv[1]);
    switch (data)
    {
      case 1:
        if (argc != 3)
        {
          throw std::invalid_argument("Error: incorrect count of arguments!\n");
        }
        task1(argv[2]);
        break;
      case 2:
        if (argc != 3)
        {
          throw std::invalid_argument("Error: incorrect count of arguments!\n");
        }
        task2(argv[2]);
        break;
      case 3:
        if (argc != 2)
        {
          throw std::invalid_argument("Error: incorrect count of arguments!\n");
        }
        task3();
        break;
      case 4:
        if (argc != 4)
        {
          throw std::invalid_argument("Error: incorrect count of arguments!\n");
        }
        task4(argv[2], std::stoi(argv[3]));
        break;
      default:
        throw std::invalid_argument("Error: entered the wrong task number!\n");
    }
  }
  catch (const std::exception &error)
  {
    std::cerr << error.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return -1;
  }
  return 0;
}
