#include "parts.hpp"
#include <iostream>
#include <string>
#include "user-interface.hpp"
#include "parse-command.hpp"
void lovkacheva::partOne()
{
  UserInterface interface(std::make_shared<lovkacheva::PhoneBook>());
  std::ios::iostate oldExceptions = std::cin.exceptions();
  std::cin.exceptions(std::istream::failbit);
  try
  {
    while (std::cin.good() && std::cin.peek() != EOF)
    {
      std::string command;
      getline(std::cin, command);
      auto executeCommand = lovkacheva::parseCommand(command, interface, std::cout);
      executeCommand();
    }
    std::cin.exceptions(oldExceptions);
  }
  catch (const std::istream::failure& e)
  {
    std::cin.exceptions(oldExceptions);
    throw;
  }
}
