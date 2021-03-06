#ifndef B3_TASK1_HPP
#define B3_TASK1_HPP

#include <iostream>
#include <sstream>
#include <memory>
#include "phoneBook.hpp"
#include "phoneBookContainer.hpp"
#include "parseAndExec.hpp"

namespace task1
{
  void exec();
  
  void exec()
  {
    PhoneBook book;
    PhoneBookContainer phoneBook(std::make_unique<PhoneBook>(book));
    std::string string;
    while (std::getline(std::cin, string))
    {
      std::stringstream sin(string);
      std::string command;
      sin >> command;
      parseAndExec(phoneBook, command, sin);
    }
    
    if (!std::cin.eof() && !std::cin.good())
    {
      throw std::ios_base::failure("Error while reading data!\n");
    }
  }
}

#endif //B3_TASK1_HPP
