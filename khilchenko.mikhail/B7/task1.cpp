#include <math.h>
#include <algorithm>
#include <functional>
#include <iterator>
#include <iostream>

#define _USE_MATH_DEFINES

void task1()
{
  std::transform(std::istream_iterator<double>(std::cin), std::istream_iterator<double>(),
      std::ostream_iterator<double>(std::cout, "\n"),
      std::bind(std::multiplies<double>(), M_PI, std::placeholders::_1));

  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error in reading data in task1");
  }
}
