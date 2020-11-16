#include <iostream>
#include <sstream>
#include <exception>
#include <memory>

#include "phoneBookInterface.hpp"
#include "commands.hpp"

void task1()
{
  PhoneBookInterface phoneBook(std::make_unique<PhoneBook>(PhoneBook()));
  std::string string;
  while(std::getline(std::cin, string))
  {
    std::istringstream istream(string);
    std::string operation;
    istream >> operation;

    if(listOfCommands.find(operation) != listOfCommands.end())
    {
      try
      {
        listOfCommands.at(operation)(istream)(phoneBook);
      }
      catch(const std::invalid_argument& e)
      {
        std::cout << e.what();
      }
    }
    else if(operation != "")
    {
      std::cout << "<INVALID COMMAND>\n";
    }
  }

  if(std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Error of reading data in task 1");
  }
}
