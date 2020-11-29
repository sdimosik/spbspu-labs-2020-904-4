#ifndef B4_TASK_ONE_HPP
#define B4_TASK_ONE_HPP
#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>

#include "dataStruct.hpp"


void task1()
{
  std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::ios_base::failure(" Error: there was a problem reading the data!\n");
  }

  std::sort(vector.begin(), vector.end());
  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
};

#endif
