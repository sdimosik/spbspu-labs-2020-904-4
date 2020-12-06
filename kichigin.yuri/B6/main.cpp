#include <iostream>
#include <algorithm>
#include <iterator>
#include "functor.hpp"

int main()
{
  try
  {
    Functor func = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Functor());
    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::runtime_error("Error while reading");
    }
    func.print(std::cout);
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }

  return 0;
}
