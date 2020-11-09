#include "parse-command.hpp"
#include <sstream>

const char* const INVALID_COMMAND = "<INVALID COMMAND>\n";

lovkacheva::Command lovkacheva::parseCommand(std::string &commandLine, UserInterface &interface, std::ostream &out)
{

  using CommandPtr = void (UserInterface::*)(std::vector<std::string>, std::ostream &);
  using CommandMap = std::unordered_map<std::string, CommandPtr>;
  std::istringstream in(commandLine);
  std::string commandName;
  in >> commandName;

  static const CommandMap COMMAND_TABLE = {{"add", &lovkacheva::UserInterface::add},
      {"store", &lovkacheva::UserInterface::store},
      {"delete", &lovkacheva::UserInterface::deleteEntry},
      {"insert", &lovkacheva::UserInterface::insertEntry},
      {"move", &lovkacheva::UserInterface::move},
      {"show", &lovkacheva::UserInterface::show}};

  CommandMap::const_iterator it = COMMAND_TABLE.find(commandName);
  if (it == COMMAND_TABLE.end())
  {
    return [&]() { ; };
  }

  std::vector<std::string> args;
  std::string argument;
  in >> std::ws;
  while (in.peek() != EOF)
  {
    in >> argument;
    if (argument[0] == '"')
    {
      while ((argument.back() != '"' || argument.size() == 1 || argument[argument.size() - 2] == '\\') && in.peek() != EOF)
      {
        std::string stringToAppend;
        getline(in, stringToAppend, '"');
        argument.append(stringToAppend + '"');
      }
      if (argument.back() != '"' || argument.size() == 1 || argument[argument.size() - 2] == '\\')
      {
        return [&]() { out << INVALID_COMMAND; };
      }
    }
    args.push_back(argument);
  }

  return [=, &out, &interface] () { (&interface->*it->second)(args, out); };
}
