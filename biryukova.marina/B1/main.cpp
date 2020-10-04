#include <iostream>
#include "tasks.hpp" 

int main(int argc, char* argv[])
{
  try
  {
    if (argc == 1)
    {
      std::cerr << "Invalid count of arguments\n";
      return 1;
    }
    int taskNumber = std::atoi(argv[1]);
    switch (taskNumber)
    {
    case 1:
      if (argc == 3)
      {
        task1(argv[2]);
        break;
      }
      std::cerr << "Invalid count of arguments\n";
      return 1;
    case 2:
      if (argc == 3)
      {
        task2(argv[2]);
        break;
      }
      std::cerr << "Invalid count of arguments\n";
      return 1;
    case 3:
      if (argc == 2)
      {
        task3();
        break;
      }
      std::cerr << "Invalid count of arguments\n";
      return 1;
    case 4:
      if (argc == 4)
      {
        task4(argv[2], argv[3]);
        break;
      }
      std::cerr << "Invalid count of arguments\n";
      return 1;
    default:
      std::cerr << "Invalid task number\n";
      return 1;
    }
  }
  catch (std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
