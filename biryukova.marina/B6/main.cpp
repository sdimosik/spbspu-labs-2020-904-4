#include <iostream>
#include "task.hpp"

int main()
{
  try
  {
    task();
  }
  catch (std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
