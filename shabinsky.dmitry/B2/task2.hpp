//
// Created by sdimosik on 11.10.2020.
//

#ifndef B2_TASK2_HPP
#define B2_TASK2_HPP

#include <list>
#include <iostream>
#include "utils.hpp"

namespace task2
{
  void exec();
  
  void exec()
  {
    int num, count = 0;
    std::list<int> list;
    
    while (std::cin >> num)
    {
      if (num < 1 || num > 20)
      {
        throw std::invalid_argument("Invalid num. Num should be 1 <= num <= 20. Have: " + std::to_string(num));
      }
      count++;
      if (count > 20)
      {
        throw std::invalid_argument("Invalid count of num. Count should be 0 <= count <= 20. Have: " + std::to_string(num));
      }
      list.push_back(num);
    }
    
    if (!std::cin.good() && !std::cin.eof())
    {
      throw std::ios_base::failure("Fail with reading data!");
    }
    utils::print<int>(list.begin(), list.end());
  }
}

#endif //B2_TASK2_HPP
