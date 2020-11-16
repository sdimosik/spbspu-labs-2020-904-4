#ifndef DATASTRUCT_HPP
#define DATASTRUCT_HPP

#include <iostream>
#include <string>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

int readKey(std::istream &);

std::istream &operator>>(std::istream &, DataStruct &);

std::ostream &operator<<(std::ostream &, const DataStruct &);

bool operator<(const DataStruct &, const DataStruct &);

#endif
