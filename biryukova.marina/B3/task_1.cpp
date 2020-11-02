#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include "phone-book-interface.hpp"
#include "commands.hpp"

void task1()
{
  PhoneBook phoneBook;
  PhoneBookInterface book(std::make_unique<PhoneBook>(phoneBook));
  std::for_each(std::istream_iterator<FunctionType>(std::cin), std::istream_iterator<FunctionType>(),
      [&](const FunctionType& function)
      {
        function(book, std::cout, std::cout);
      });
  if (std::cin.fail() && !std::cin.eof())
  {      
    throw std::runtime_error("Error while reading in task 1");
  }
}
