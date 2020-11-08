#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <map>
#include <iosfwd>
#include <functional>
#include "phoneBookInterface.hpp"

using function = std::function<void(phoneBookInterface &phoneBook, std::ostream &out)>;

function printError();

function add(std::istream &sin);

function store(std::istream &sin);

function insert(std::istream &sin);

function erase(std::istream &sin);

function show(std::istream &sin);

function move(std::istream &sin);

std::istream &operator>>(std::istream &input, function &function);

static const std::map<std::string, std::function<function(std::istream &)>> TABLE =
{
  {"add", add},
  {"store", store},
  {"insert", insert},
  {"delete", erase},
  {"show", show},
  {"move", move}
};

#endif
