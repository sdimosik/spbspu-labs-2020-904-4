#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <functional>
#include <algorithm>
#include <iterator>

void task1()
{
  auto functor = std::bind(std::multiplies<double>(), M_PI, std::placeholders::_1);
  std::transform(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(), 
      std::ostream_iterator<double>(std::cout, "\n"), functor);
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error while reading in task 1");
  }
}
