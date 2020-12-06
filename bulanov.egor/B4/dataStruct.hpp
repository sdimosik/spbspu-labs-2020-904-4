#ifndef B4_DATASTRUCT_HPP
#define B4_DATASTRUCT_HPP

#include <string>
#include <iostream>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;

  bool operator<(const DataStruct &data) const;
};

std::ostream& operator<<(std::ostream& out, const DataStruct& data);
std::istream& operator>>(std::istream& in, DataStruct& data);

#endif
