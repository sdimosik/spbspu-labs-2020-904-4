#define _USE_MATH_DEFINES

#include <iterator>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <functional>

void task1()
{
  auto functor = std::bind(std::multiplies<double>(), M_PI, std::placeholders::_1);
  std::transform(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(),std::ostream_iterator<double>(std::cout, "\n"), functor);

  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error in task 1");
  }
}

