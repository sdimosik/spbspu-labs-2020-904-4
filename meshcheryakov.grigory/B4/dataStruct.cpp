#include <stdexcept>
#include <iostream>
#include <string>
#include <sstream>
#include "dataStruct.hpp"

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  std::string string;
  if (!getline(in, string))
  {
    return in;
  }
  std::istringstream sin(string);
  char comma1 = '\0';
  int key1 = 0;
  sin >> key1 >> comma1;

  char comma2 = '\0';
  int key2 = 0;
  sin >> key2 >> comma2;

  if (!checkInput(key1, comma1) || !checkInput(key2, comma2))
  {
    throw std::invalid_argument("Invalid DataStruct.");
  }

  std::string str;
  std::getline(sin >> std::ws, str);
  if (!sin.eof() && sin.fail())
  {
    throw std::invalid_argument("Invalid DataStruct. String is empty.");
  }

 dataStruct = {key1, key2, str};

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  out << dataStruct.key1 << "," << dataStruct.key2 << "," << dataStruct.str;
  return out;
}

bool comparator(const DataStruct& first, const DataStruct& second)
{
  if (first.key1 != second.key1)
  {
    return first.key1 < second.key1;
  }
  if (first.key2 != second.key2)
  {
    return first.key2 < second.key2;
  }

  return first.str.size() < second.str.size();
}

bool checkInput(const int key, const char comma)
{
  return (abs(key)<=5 && comma == ',');
}
