#ifndef B3_COMMANDS_HPP
#define B3_COMMANDS_HPP

#include <iostream>
#include <iosfwd>
#include <functional>
#include <map>
#include "phoneBookInterface.hpp"

using function = std::function<void(PhoneBookInterface &phoneBookInterface, std::ostream &out)>;

function add(std::istream &in);

function store(std::istream &in);

function insert(std::istream &in);

function erase(std::istream &in);

function show(std::istream &in);

function move(std::istream &in);

function printOutErrors();

std::istream &operator>>(std::istream &input, function &function);

static const std::map<std::string, std::function<function(std::istream &)>> COMMAND_MEANS =
{
  {"add",    add},
  {"store",  store},
  {"insert", insert},
  {"delete", erase},
  {"show",   show},
  {"move",   move}
};



#endif
