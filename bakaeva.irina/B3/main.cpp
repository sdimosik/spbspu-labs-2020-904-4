#include <iostream>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Incorrect count of arguments");
    }

    int task = std::stoi(argv[1]);
    switch (task)
    {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
      default:
        throw std::invalid_argument("Incorrect number of task!");
    }
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << std::endl;
    return 2;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return 2;
  }
  return 0;
}
