#ifndef B3_DATAVALIDATION_HPP
#define B3_DATAVALIDATION_HPP

#include <string>

std::string getCheckedName(std::istream &sin);

std::string getCheckedNumber(std::istream &sin);

std::string getCheckedBookmark(std::istream &sin);

bool checkSteps(const std::string &steps);

int getSteps(std::string steps);

#endif
