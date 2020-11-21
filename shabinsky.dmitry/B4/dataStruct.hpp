#ifndef B4_DATASTRUCT_HPP
#define B4_DATASTRUCT_HPP

#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

bool isValidRange(int key);

int readKey(std::istream &in);

std::istream &operator>>(std::istream &in, DataStruct &data);

std::ostream &operator<<(std::ostream &out, const DataStruct &data);

bool operator<(const DataStruct &data1, const DataStruct &data2);

#endif //B4_DATASTRUCT_HPP
