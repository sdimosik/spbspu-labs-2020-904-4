#include <iostream>
#include "task_1.hpp"

int main()
{
  try
  {
    task_1();
  }

  catch (std::exception& exception)
  {
    std::cerr << exception.what() << "\n";
    return 1;
  }
  return 0;
}
