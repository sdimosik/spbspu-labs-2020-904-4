#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <string>
#include <iosfwd>
#include <functional>
#include <map>
#include "phone-book-interface.hpp"

const std::string ADD = "add";
const std::string STORE = "store";
const std::string INSERT = "insert";
const std::string BEFORE = "before";
const std::string AFTER = "after";
const std::string DELETE = "delete";
const std::string SHOW = "show";
const std::string MOVE = "move";

using FunctionType = std::function<void(PhoneBookInterface&, std::ostream&, std::ostream&)>;

std::string parseName(std::istream& input);
std::string parseNumber(std::istream& input);
std::string parseMark(std::istream& input);
FunctionType printInvalid();
FunctionType add(std::istream& input);
FunctionType store(std::istream& input);
FunctionType insertBookmark(std::istream& input);
FunctionType deleteBookmark(std::istream& input);
FunctionType showBookmark(std::istream& input);
FunctionType move(std::istream& input);
std::istream& operator >>(std::istream& input, FunctionType& function);

static const std::map <const std::string, std::function<FunctionType(std::istream&)>> table = 
{
  {ADD, add},
  {STORE, store},
  {INSERT, insertBookmark},
  {DELETE, deleteBookmark},
  {SHOW, showBookmark},
  {MOVE, move}
};
    
#endif
