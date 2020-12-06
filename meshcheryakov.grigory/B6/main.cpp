#include <iostream>
#include "task.hpp"

int main()
{
  try
  {
    task();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return 2;
  }
  catch (...)
  {
    std::cerr << "Unknown error!" << std::endl;
    return 2;
  }

  return 0;
}
