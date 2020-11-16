#include <iostream>
#include "task.hpp"

int main()
{
  try
  {
    task::exec();
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << std::endl;
    return -1;
  }
  catch (...)
  {
    std::cerr << "Error occurred\n";
    return -1;
  }
  return 0;
}
