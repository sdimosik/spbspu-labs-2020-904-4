#ifndef SPBSPU_LABS_2020_904_4_COMMANDS_HPP
#define SPBSPU_LABS_2020_904_4_COMMANDS_HPP

#include "phoneBookInterface.hpp"
#include <iostream>
#include <map>
#include <functional>
#include <iosfwd>
#include <string>

using function = std::function<void(PhoneBookInterface &phoneBook, std::ostream &out)>;

std::string checkNumber(std::istream &sin);

std::string checkBookmarkName(std::istream &sin);

std::string checkName(std::istream &sin);

int getSteps(const std::string &step);

function add(std::istream &sin);

function store(std::istream &sin);

function insert(std::istream &sin);

function deleteBookmark(std::istream &sin);

function show(std::istream &sin);

function move(std::istream &sin);

function printException();

std::istream &operator>>(std::istream &sin, function &function);

static const std::map<std::string, std::function<function(std::istream &)>> TABLE =
    {
        {"add",    add},
        {"store",  store},
        {"insert", insert},
        {"delete", deleteBookmark},
        {"show",   show},
        {"move",   move}
    };

#endif
