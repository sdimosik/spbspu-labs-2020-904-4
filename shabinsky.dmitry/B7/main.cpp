#include <iostream>
#include <string>
#include "tasks.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of arguments");
    }
    int token = std::stoi(argv[1]);
    switch (token)
    {
      case 1:
        tasks::exec1();
        break;
      case 2:
        tasks::exec2();
        break;
      default:
        throw std::invalid_argument("Task number must be between 1 and 2");
    }
  }
  catch (const std::exception &exception)
  {
    std::cerr << exception.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Error occurred" << std::endl;
    return -1;
  }
  
  return 0;
}
