#include "tasks.hpp"
#include <vector>
#include "functions.hpp"

void task::doFourthTask(const char* sortDirection, size_t size)
{
  std::vector<double> vector(size);
  detail::fillRandom(&vector[0], size);
  detail::printContainer<std::vector<double>>(vector);
  std::function<bool(double, double)> compare = detail::getCompare<double>(sortDirection);
  detail::sortContainer<detail::AccessByIndex>(vector, compare);
  detail::printContainer<std::vector<double>>(vector);
}
