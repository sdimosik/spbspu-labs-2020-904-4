#include <iostream>

#include "shape.hpp"

void task1();
void task2();

int main(int argc, char* argv[])
{
    try
    {
    if (argc != 2)
      {
        throw std::invalid_argument("Invalid number of arguments");
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
        throw std::invalid_argument("Invalid task");
      }
    }

    catch (std::exception& exc)
    {
      std::cerr << exc.what() << "\n";
      return 1;
    }

    return 0; 
}
