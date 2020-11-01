//
// Created by sdimosik on 29.10.2020.
//

#ifndef B3_COMMAND_HPP
#define B3_COMMAND_HPP

#include <istream>
#include <iostream>
#include "phoneBookContainer.hpp"

const std::string INVALID_COMMAND = "<INVALID COMMAND>\n";
const std::string INVALID_STEP = "<INVALID STEP>\n";

bool isNameValid(std::string &name);

bool isNumberValid(std::string &number);

bool isBookmarkValid(std::string &bookmark);

void addCommand(PhoneBookContainer &phoneBook, std::istream &sin);

void storeCommand(PhoneBookContainer &phoneBook, std::istream &sin);

void insertCommand(PhoneBookContainer &phoneBook, std::istream &sin);

void eraseCommand(PhoneBookContainer &phoneBook, std::istream &sin);

void showCommand(PhoneBookContainer &phoneBook, std::istream &sin);

void moveCommand(PhoneBookContainer &phoneBook, std::istream &sin);

void parseCommand(PhoneBookContainer &phoneBook, const std::string &command, std::istream &sin);

#endif //B3_COMMAND_HPP
