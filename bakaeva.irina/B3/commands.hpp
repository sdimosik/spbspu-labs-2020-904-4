#ifndef B3_COMMANDS_HPP
#define B3_COMMANDS_HPP

#include <iostream>
#include <iosfwd>
#include <functional>
#include <map>
#include "phoneBookInterface.hpp"

using function = std::function<void(PhoneBookInterface &phoneBook, std::ostream &out)>;

function add(std::istream &sin);

function store(std::istream &sin);

function insert(std::istream &sin);

function erase(std::istream &sin);

function show(std::istream &sin);

function move(std::istream &sin);

function printException();

std::istream &operator>>(std::istream &input, function &function);

static const std::map<std::string, std::function<function(std::istream &)>> CALL_TABLE =
{
  {"add",    add},
  {"store",  store},
  {"insert", insert},
  {"delete",  erase},
  {"show",   show},
  {"move",   move}
};

#endif
