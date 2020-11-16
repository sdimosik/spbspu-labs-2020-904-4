#ifndef B3_PARSE_HPP
#define B3_PARSE_HPP

#include "phoneBookContainer.hpp"

namespace parse
{
  const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";
  const std::string INVALID_STEP = "<INVALID STEP>\n";
  
  bool isNameValidPlusCorrect(std::string &name);
  
  bool isNumberValid(std::string &number);
  
  bool isBookmarkValid(std::string &bookmark);
  
  void addCommand(bool &execCommand, std::string &number, std::string &name, std::istream &sin);
  
  void storeCommand(bool &execCommand, std::string &bookmark, std::string &newBookmark, std::istream &sin);
  
  void
  insertCommand(bool &execCommand, std::string &direction, std::string &bookmark, std::string &number,
                std::string &name,
                std::istream &sin);
  
  void eraseCommand(bool &execCommand, std::string &bookmark, std::istream &sin);
  
  void showCommand(bool &execCommand, std::string &bookmark, std::istream &sin);
  
  void moveCommand(bool &execCommand, std::string &bookmark, std::string &steps, std::istream &sin);
  
  void
  exec(bool &execCommand, const std::string &command, std::istream &sin, std::string &direction, std::string &bookmark,
       std::string &newBookmark,
       std::string &number, std::string &name, std::string &steps);
}

#endif //B3_PARSE_HPP
