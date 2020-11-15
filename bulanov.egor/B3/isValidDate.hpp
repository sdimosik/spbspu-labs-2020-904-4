#ifndef B3_ISVALIDDATE_HPP
#define B3_ISVALIDDATE_HPP

#include <string>

std::string checkNumber(std::istream& number);

std::string checkName(std::istream& name);

std::string checkBookmark(std::istream& bookmark);

bool checkStep(const std::string &step);

int getStep(std::string steps);

#endif
