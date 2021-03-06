#ifndef B1_TASK1_HPP
#define B1_TASK1_HPP

#include <iostream>
#include <vector>
#include <forward_list>
#include "access.hpp"
#include "utils.hpp"

namespace task1
{
  void exec(const char *sortType);
  
  void exec(const char *sortType)
  {
    std::vector<int> vector;
    int in;
    
    while (std::cin >> in)
    {
      if (std::cin.fail())
      {
        throw std::invalid_argument("Invalid data. Task 1");
      }
      vector.push_back(in);
    }
    
    if (!std::cin.eof() && !std::cin.good())
    {
      throw std::ios_base::failure("Fail with reading data. Task 1");
    }
    
    std::vector<int> vectorAt(vector);
    std::forward_list<int> list(vector.begin(), vector.end());
    
    utils::bubbleSort<IndexAccess>(vector, utils::compareOrder<int>(utils::getArgSort(sortType)));
    utils::println(vector);
    
    utils::bubbleSort<AtAccess>(vectorAt, utils::compareOrder<int>(utils::getArgSort(sortType)));
    utils::println(vectorAt);
    
    utils::bubbleSort<IteratorAccess>(list, utils::compareOrder<int>(utils::getArgSort(sortType)));
    utils::println(list);
  }
}

#endif //B1_TASK1_HPP
