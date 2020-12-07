#include <iostream>
#include "dataStruct.hpp"

void task();

int main()
{
  try
  {
    task();
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error.\n";
    return 2;
  }
  return 0;
}
