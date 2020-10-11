//
// Created by sdimosik on 11.10.2020.
//

#ifndef B2_TASK1_HPP
#define B2_TASK1_HPP

#include <sstream>
#include <string>
#include <iostream>
#include "queuePriority.hpp"
#include "utils.hpp"

namespace task1
{
  void exec();
  
  void exec()
  {
    queuePriority<std::string> queuePriority;
    std::string lineIn;
    
    while (getline(std::cin, lineIn))
    {
      if (!std::cin.good() && !std::cin.eof())
      {
        throw std::ios_base::failure("Fail with reading data!");
      }
      
      std::stringstream in(lineIn);
      std::string command;
      in >> command;
      
      if (command == "add")
      {
         utils::add(queuePriority, in, std::cout);
      }
      else if (command == "get")
      {
        utils::get(queuePriority, std::cout);
      }
      else if (command == "accelerate")
      {
        utils::accelerate(queuePriority);
      }
      else
      {
        std::cout << utils::INVALID_COMMAND << "\n";
      }
    }
    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::runtime_error("Invalid input");
    }
  }
}

#endif //B2_TASK1_HPP
