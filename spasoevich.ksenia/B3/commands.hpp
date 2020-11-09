#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <string>
#include <iosfwd>
#include <map>
#include <functional>
#include "phonebook-interface.hpp"

using Function = std::function<void(phoneBookInterface&, std::ostream&, std::ostream&)>;
std::istream& operator >>(std::istream& input, Function& function);
std::string getName(std::istream& input);
std::string getNumber(std::istream& input);
std::string getMarkName(std::istream& input);
Function add(std::istream& input);
Function store(std::istream& input);
Function insert(std::istream& input);
Function deleteRecord(std::istream& input);
Function show(std::istream& input);
Function move(std::istream& input);
Function printInvalid();

static const std::map <const std::string, std::function<Function(std::istream&)>> table = 
{
  {"add", add},
  {"store", store},
  {"insert", insert},
  {"delete", deleteRecord},
  {"show", show},
  {"move", move}
};

#endif
