#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#include <string>
#include <iostream>

struct DataStructure
{
  int key1;
  int key2;
  std::string str;
};

bool isNumberCorrect(const int number);

bool operator<(const DataStructure& first, const DataStructure& second);

std::istream& operator>>(std::istream& in, DataStructure& data);

std::ostream& operator<<(std::ostream& out, const DataStructure& data);

#endif
