#ifndef PARSE_COMMAND_HPP
#define PARSE_COMMAND_HPP
#include <functional>
#include "user-interface.hpp"
namespace lovkacheva
{
  using Command = std::function<void()>;
  Command parseCommand(std::string &commandLine, UserInterface& interface, std::ostream &out);
}
#endif
