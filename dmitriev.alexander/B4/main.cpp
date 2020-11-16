#include <iostream>
#include "task.hpp"

int main()
{
  try
  {
    task();
  }
  catch (const std::exception &exc)
  {
    std::cerr << exc.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Error occurred!" << std::endl;
    return -1;
  }

  return 0;
}
