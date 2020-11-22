#include <iostream>
#include <stdexcept>
#include <algorithm>
#include <functional>
#include <iterator>
#include "phoneBookInterface.hpp"
#include "commands.hpp"


void task1()
{
  PhoneBook book;
  PhoneBookInterface bookInterface(std::make_unique<PhoneBook>(book));
  using iterator = std::istream_iterator<std::function<void(PhoneBookInterface& phoneBook, std::ostream& output)>>;
  std::for_each(iterator(std::cin), iterator(), [&](auto& function)
    {
      function(bookInterface, std::cout);
    });
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Task 1: Reading data failure!");
  }

}
