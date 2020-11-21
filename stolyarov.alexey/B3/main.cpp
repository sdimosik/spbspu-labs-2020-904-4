#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("ERROR: Invalid number of arguments!\n");
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
      throw std::invalid_argument("ERROR: Invalid task number: " + std::to_string(task) + " Should be 1 or 2!\n");
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown problem!\n";
    return 2;
  }
  return 0;
}
