#ifndef B1_TASK3_HPP
#define B1_TASK3_HPP

#include <iostream>
#include <vector>
#include "utils.hpp"

namespace task3
{
  void exec();
  
  void exec()
  {
    std::vector<int> vector;
    int in = 0;
    
    while (std::cin >> in)
    {
      if (in == 0)
      {
        break;
      }
      vector.push_back(in);
    }
    
    if (!std::cin.eof() && !std::cin.good())
    {
      throw std::ios_base::failure("Fail with reading data");
    }
    
    if (vector.empty())
    {
      return;
    }
  
    if (in != 0)
    {
      throw std::ios_base::failure("Fail with read number!");
    }
    
    bool isOne = false;
    if (vector.back() == 1)
    {
      isOne = true;
    }
    
    if (vector.back() == 1 || vector.back() == 2)
    {
      auto it = vector.begin();
      while (it != vector.end())
      {
        if (!isOne && (*it % 3 == 0))
        {
          it = vector.insert(++it, 3, 1) + 3;
        }
        else if (isOne && (*it % 2 == 0))
        {
          it = vector.erase(it);
        }
        else
        {
          ++it;
        }
      }
    }
    utils::print(vector);
  }
}

#endif //B1_TASK3_HPP
