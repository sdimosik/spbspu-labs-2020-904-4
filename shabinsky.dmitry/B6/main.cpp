#include <iostream>
#include "task.hpp"

int main()
{
  try
  {
    task::exec();
  }
  catch (const std::exception &exception)
  {
    std::cerr << exception.what() << std::endl;
    return 2;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return 2;
  }
  
  return 0;
}
