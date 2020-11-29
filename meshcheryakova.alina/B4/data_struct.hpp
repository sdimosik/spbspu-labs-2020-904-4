#ifndef B4_DATA_STRUCT_HPP
#define B4_DATA_STRUCT_HPP

#include <iostream>
#include <algorithm>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;

  bool operator <(const DataStruct& data) const;
};

std::istream& operator >>(std::istream& in, DataStruct& data);
std::ostream& operator <<(std::ostream& out, const DataStruct& data);

#endif //B4_DATA_STRUCT_HPP
