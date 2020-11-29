#include <iostream>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Invalid count of args!");
    }

    int part = atoi(argv[1]);

    if (part == 1)
    {
      task1();
    }
    else if (part == 2)
    {
      task2();
    }
    else
    {
      throw std::invalid_argument("Invalid task number!");
    }

    return 0;
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem!";
    return 2;
  }
}
