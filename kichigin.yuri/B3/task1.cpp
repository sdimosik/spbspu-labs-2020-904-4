#include <iostream>
#include <string>
#include <sstream>
#include <stdexcept>
#include "book-interface.hpp"
#include "commands.hpp"

void task1()
{
  TelephoneBook book;
  BookInterface telephoneBookInterface(book);
  std::string string;
  while (std::getline(std::cin, string))
  {
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::runtime_error("Error while reading");
    }

    std::istringstream istream(string);
    std::string command;
    istream >> command;
    if (commandList.find(command) != commandList.end())
    {
      commandList[command](istream, telephoneBookInterface);
    }
    else
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }
}
