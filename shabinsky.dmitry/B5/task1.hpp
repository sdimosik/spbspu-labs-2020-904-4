#ifndef B5_TASK1_HPP
#define B5_TASK1_HPP

#include <iostream>
#include <string>
#include <unordered_set>
#include <iterator>

namespace task1
{
  void exec();
  
  void exec()
  {
    std::unordered_set<std::string>
      vector((std::istream_iterator<std::string>(std::cin)), std::istream_iterator<std::string>());
    
    if ((!std::cin.eof()) && (std::cin.fail()))
    {
      throw std::invalid_argument("Error while reading data!\n");
    }
    
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
  }
}

#endif //B5_TASK1_HPP
