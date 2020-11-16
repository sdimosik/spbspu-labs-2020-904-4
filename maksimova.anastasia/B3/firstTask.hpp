#ifndef FIRSTTASK_HPP
#define FIRSTTASK_HPP

#include <iostream>
#include <string>
#include <iterator>
#include <algorithm>
#include <memory>
#include "phoneBookInterface.hpp"
#include "commands.hpp"

void firstTask()
{
  phoneBook book;
  phoneBookInterface phoneBook(std::make_unique<phoneBook>(book));
  std::for_each(std::istream_iterator<function>(std::cin), std::istream_iterator<function>(),
      [&](auto& function)
      {
        function(phoneBook, std::cout);
      });
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error by reading data in first task!");
  }
}

#endif
