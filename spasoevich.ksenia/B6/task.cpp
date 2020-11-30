#include "task.hpp"

#include <algorithm>

StatsCollector::StatsCollector() :
  max(0),
  min(0),
  mean(0),
  positive(0),
  negative(0),
  evenSum(0),
  oddSum(0),
  firstEqLast(true),
  size(0)
{}

void StatsCollector::operator()(int num)
{
  num % 2 ? oddSum += num : evenSum += num;
  if (num != 0)
  {
    num > 0 ? positive++ : negative++;
  }

  if (size++ == 0)
  {
    first = max = min = mean = num;
  }
  else
  {
    max = std::max(max, num);
    min = std::min(min, num);
    mean = static_cast<double>(evenSum + oddSum) / size;
    firstEqLast = first == num;
  }
}
