#ifndef TASK_HPP
#define TASK_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

void task()
{
  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());
  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Error while reading data!\n");
  }
  std::sort(vector.begin(), vector.end());

  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
}

#endif
