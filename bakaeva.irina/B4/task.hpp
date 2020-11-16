#ifndef B4_TASK_HPP
#define B4_TASK_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "dataStruct.hpp"

void task()
{
  std::vector<DataStruct> vector;
  DataStruct data;
  while (std::cin >> data)
  {
    vector.push_back(data);
  }

  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::invalid_argument("Error by reading data!");
  }

  std::sort(vector.begin(), vector.end(), [&](DataStruct &current, DataStruct &next)
  {
    if (current.key1 == next.key1 && current.key2 == next.key2)
    {
      return (current.str.length() < next.str.length());
    }
    else if (current.key1 == next.key1)
    {
      return (current.key2 < next.key2);
    }
    else
    {
      return (current.key1 < next.key1);
    }
  });

  std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
}

#endif
