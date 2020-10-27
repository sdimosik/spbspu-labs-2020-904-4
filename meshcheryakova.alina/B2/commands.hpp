#ifndef B2_COMMANDS_HPP
#define B2_COMMANDS_HPP

#include <iostream>

typedef enum
{
  ADD,
  GET,
  ACCELERATE,
  WRONG_COMMAND
} Commands;

std::istream& operator >> (std::istream& input, Commands& elem)
{
  std::string command;
  input >> command;
  if (command == "add")
  {
    elem = ADD;
  }
  else if (command == "get")
  {
    elem = GET;
  }
  else if (command == "accelerate")
  {
    elem = ACCELERATE;
  }
  else
  {
    elem = WRONG_COMMAND;
  }
  return input;
}

#endif //B2_COMMANDS_HPP
