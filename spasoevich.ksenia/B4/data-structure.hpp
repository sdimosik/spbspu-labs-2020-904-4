#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#include <string>
#include <iostream>

const int LOWER_LIMIT = -5;
const int UPPER_LIMIT = 5;

struct DataStructure
{
  int key1;
  int key2;
  std::string str;
};

bool isNumberInCorrectRange(const int number);
bool operator<(const DataStructure& first, const DataStructure& second);
std::istream& operator>>(std::istream& in, DataStructure& data);
std::ostream& operator<<(std::ostream& out, const DataStructure& data);

#endif


