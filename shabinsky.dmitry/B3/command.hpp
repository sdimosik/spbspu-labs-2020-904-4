//
// Created by sdimosik on 29.10.2020.
//

#ifndef B3_COMMAND_HPP
#define B3_COMMAND_HPP

#include <istream>
#include <iostream>
#include "phoneBookContainer.hpp"

namespace command
{
  void addCommand(PhoneBookContainer &phoneBook, std::string &number, std::string &name);
  
  void storeCommand(PhoneBookContainer &phoneBook, std::string &bookmark, std::string &newBookmark);
  
  void insertCommand(PhoneBookContainer &phoneBook, std::string &direction, std::string &bookmark, std::string &number,
                     std::string &name);
  
  void eraseCommand(PhoneBookContainer &phoneBook, std::string &bookmark);
  
  void showCommand(PhoneBookContainer &phoneBook, std::string &bookmark);
  
  void moveCommand(PhoneBookContainer &phoneBook, std::string &bookmark, std::string &steps);
  
  void exec(PhoneBookContainer &phoneBook, const std::string &command, std::string &direction,
            std::string &bookmark,
            std::string &newBookmark,
            std::string &number, std::string &name, std::string &steps);
}
#endif //B3_COMMAND_HPP
