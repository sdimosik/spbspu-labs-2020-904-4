#include <iostream>
#include <sstream>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <string>
#include "commands.hpp"
#include "phonebook-interface.hpp"

void task1()
{
  phoneBook book; 
  phoneBookInterface contact(std::make_unique<phoneBook>(book));

  std::for_each(std::istream_iterator<Function>(std::cin), std::istream_iterator<Function>(),[&](const Function& function)
  {
      function(contact, std::cout, std::cout);
  });

    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::runtime_error("Failed to read!\n");
    }
}
