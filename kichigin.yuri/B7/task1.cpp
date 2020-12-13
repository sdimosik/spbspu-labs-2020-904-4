#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <functional>
#include <cmath>

void task1()
{
  std::transform(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(),
    std::ostream_iterator<double>(std::cout,"\n"), std::bind(std::multiplies<double>(), std::placeholders::_1, M_PI));
  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::runtime_error("Error while reading");
  }
}
