#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Error: wrong amount of argc entered!\n");
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
        throw std::invalid_argument("Error: wrong task number entered!\n");
    }
  }
  catch (const std::exception &except)
  {
    std::cerr << except.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return 2;
  }
  return 0;
}
