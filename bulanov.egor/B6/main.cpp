#include <iostream>
#include "task_one.hpp"

int main()
{
  try
  {
    task1();
  }
  catch (const std::exception &except)
  {
    std::cerr << except.what() << std::endl;
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return 2;
  }
  return 0;
}

