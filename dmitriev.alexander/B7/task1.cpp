#include <iostream>
#include <cmath>
#include <functional>
#include <algorithm>
#include <iterator>

void task1()
{
  auto multiplier = std::bind(std::multiplies<float>(), std::placeholders::_1, M_PI);

  std::transform((std::istream_iterator<float>(std::cin)), std::istream_iterator<float>(),
    std::ostream_iterator<float>(std::cout, "\n"), multiplier);

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::ios::failure("Fail while reading data!");
  }
}
