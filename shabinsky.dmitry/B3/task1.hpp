#ifndef B3_TASK1_HPP
#define B3_TASK1_HPP

#include <sstream>
#include "phoneBookContainer.hpp"
#include "command.hpp"

namespace task1
{
  void exec();
  
  void exec()
  {
    phoneBookContainer phoneBook;
    std::string string;
    while (std::getline(std::cin, string))
    {
      std::stringstream sin(string);
      std::string command;
      sin >> command;
      parseCommand(phoneBook, command, sin);
    }
    
    if (!std::cin.eof() && !std::cin.good())
    {
      throw std::ios_base::failure("Error while reading data!\n");
    }
  }
}

#endif //B3_TASK1_HPP
