#include <iostream>
#include "task1.hpp"
#include "task2.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of arguments");
    }
    int taskNumber = std::stoi(argv[1]);
    switch (taskNumber)
    {
      case 1:
        task1::exec();
        break;
      case 2:
        task2::exec();
        break;
      default:
        throw std::invalid_argument("Incorrect args. Task number must be between 1 and 2");
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "error occurred" << std::endl;
    return -1;
  }
  return 0;
}
