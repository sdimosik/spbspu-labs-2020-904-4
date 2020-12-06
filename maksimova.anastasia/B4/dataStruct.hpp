#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP
#include <string>

const int MAX_KEY = 5;
const int MIN_KEY = -5;

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& in, DataStruct& data);
std::ostream& operator<<(std::ostream& out, const DataStruct& data);

#endif
