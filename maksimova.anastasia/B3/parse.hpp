#ifndef PARSE_HPP
#define PARSE_HPP

#include <string>

std::string parseName(std::istream &sin);
std::string parseNumber(std::istream &sin);
std::string getCheckedBookmark(std::istream &sin);
int stepsToInt(std::string steps);
bool isValidSteps(const std::string &step);

#endif
