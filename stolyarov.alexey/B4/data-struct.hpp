#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <string>
#include <iostream>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator >>(std::istream& in, DataStruct& dataStruct);
std::ostream& operator <<(std::ostream& out, const DataStruct& dataStruct);

bool checkCondition(const DataStruct& first, const DataStruct& second);
bool checkInput(const int key, const char comma);

#endif
