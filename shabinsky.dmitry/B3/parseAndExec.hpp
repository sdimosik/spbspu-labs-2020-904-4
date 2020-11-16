#ifndef B3_PARSEANDEXEC_HPP
#define B3_PARSEANDEXEC_HPP

#include "phoneBookContainer.hpp"
#include "parse.hpp"
#include "command.hpp"

void parseAndExec(PhoneBookContainer &phoneBook, const std::string &command, std::istream &sin)
{
  bool execCommand = true;
  std::string direction, bookmark, newBookmark, number, name, steps;
  parse::exec(execCommand, command, sin, direction, bookmark, newBookmark, number, name, steps);
  if (execCommand)
  {
    command::exec(phoneBook, command, direction, bookmark, newBookmark, number, name, steps);
  }
}

#endif //B3_PARSEANDEXEC_HPP
