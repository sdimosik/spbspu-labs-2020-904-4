#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <functional>
#include <sstream>
#include "phoneBookInterface.hpp"

std::function<void(PhoneBookInterface&)> addRecord(std::istream&);

std::function<void(PhoneBookInterface&)> storeMark(std::istream&);

std::function<void(PhoneBookInterface&)> insertRecord(std::istream&);

std::function<void(PhoneBookInterface&)> deleteMark(std::istream&);

std::function<void(PhoneBookInterface&)> showMark(std::istream&);

std::function<void(PhoneBookInterface&)> moveMark(std::istream&);

static const std::map<std::string, std::function<std::function<void(PhoneBookInterface&)>(std::istream&)>> listOfCommands
    = {
        {"add", addRecord},
        {"store", storeMark},
        {"insert", insertRecord},
        {"delete", deleteMark},
        {"show", showMark},
        {"move", moveMark}
      };

#endif
