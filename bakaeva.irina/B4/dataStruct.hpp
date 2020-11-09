#ifndef B4_DATASTRUCT_HPP
#define B4_DATASTRUCT_HPP
#include <string>
#include <iostream>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& cin, DataStruct& data);
std::ostream& operator<<(std::ostream& cout, const DataStruct& data);

#endif
