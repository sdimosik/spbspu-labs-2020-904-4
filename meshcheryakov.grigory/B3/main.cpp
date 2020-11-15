#include "tasks.hpp"
#include <iostream>

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Incorrect count\n");
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
        throw std::invalid_argument("Invalid task number!\n");
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem!\n";
    return 2;
  }
  return 0;
}
