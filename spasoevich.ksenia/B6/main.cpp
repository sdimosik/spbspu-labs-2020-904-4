#include <iostream>
#include <iterator>
#include <algorithm>

#include "task.hpp"

int main()
{
  StatsCollector collector = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), StatsCollector());

  if (std::cin.fail() && !std::cin.eof())
  {
    std::cerr << "Incorrect input\n";
    return 1;
  }

  if (!collector.size)
  {
    std::cout << "No Data\n";
    return 0;
  }

  std::cout << "Max: " << collector.max
    << "\nMin: " << collector.min
    << "\nMean: " << std::fixed << collector.mean
    << "\nPositive: " << collector.positive
    << "\nNegative: " << collector.negative
    << "\nOdd Sum: " << collector.oddSum
    << "\nEven Sum: " << collector.evenSum
    << "\nFirst/Last Equal: " << (collector.firstEqLast ? "yes" : "no") << "\n";
  return 0;
}
