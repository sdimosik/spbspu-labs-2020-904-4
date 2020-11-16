#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include "phoneBookInterface.hpp"
#include "commands.hpp"

void task1()
{
  PhoneBook phoneBook;
  PhoneBookInterface phoneBookInterface(std::make_unique<PhoneBook>(phoneBook));

  using iterator = std::istream_iterator<std::function<void(PhoneBookInterface &phoneBookInterface, std::ostream &output)>>;

  std::for_each(iterator(std::cin), iterator(), [&](auto &function)
  {
    function(phoneBookInterface, std::cout);
  });

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Error: there was a problem reading the data!\n");
  }
}

