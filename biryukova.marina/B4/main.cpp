#include <iostream>
#include "algorithm.hpp"

int main()
{
  try
  {
    algorithm();
  }
  catch (std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
