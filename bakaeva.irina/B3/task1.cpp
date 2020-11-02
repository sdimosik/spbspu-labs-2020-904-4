#include <iostream>
#include <algorithm>
#include <iterator>
#include <functional>
#include "phoneBookInterface.hpp"
#include "commands.hpp"

void task1()
{
  PhoneBook book;
  PhoneBookInterface phoneBook(std::make_unique<PhoneBook>(book));

  using iterator = std::istream_iterator<std::function<void(PhoneBookInterface &phoneBook, std::ostream &output)>>;

  std::for_each(iterator(std::cin), iterator(), [&](auto &function)
  {
    function(phoneBook, std::cout);
  });

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Error by reading data!");
  }
}
