#include "data-struct.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>

const int MIN_KEY = -5;
const int MAX_KEY = 5;

namespace details
{
  int stringToKey(std::string keyString)
  {
    int sign = 1;
    if (keyString[0] == '-')
    {
      keyString.erase(0, 1);
      sign = -1;
    }

    for (size_t i = 0; i < keyString.length(); ++i)
    {
      if (!isdigit(keyString[i]))
      {
        throw std::invalid_argument("Invalid key including not only digits");
      }
    }

    int key = atoi(keyString.c_str()) * sign;
    if (key < MIN_KEY || key > MAX_KEY)
    {
      throw std::out_of_range("Key out of range");
    }
    return key;
  }
}

std::istream& operator>>(std::istream& in, DataStruct& dataStruct)
{
  if (in.eof())
  {
    in.setstate(in.failbit);
    return in;
  }
  std::string line;
  std::getline(in, line);
  if (line.empty())
  {
    in.setstate(in.failbit);
    return in;
  }

  std::istringstream stringIn(line);
  std::string key1String;
  getline(stringIn, key1String, ',');
  if (key1String.empty())
  {
    in.setstate(in.failbit);
    return in;
  }
  dataStruct.key1 = details::stringToKey(key1String);
  stringIn >> std::ws;

  std::string key2String;
  getline(stringIn, key2String, ',');
  if (key2String.empty())
  {
    in.setstate(in.failbit);
    return in;
  }
  dataStruct.key2 = details::stringToKey(key2String);
  stringIn >> std::ws;

  getline(stringIn, dataStruct.str);
  if (dataStruct.str.empty())
  {
    in.setstate(in.failbit);
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  out << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str << '\n';
  return out;
}

bool operator<(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept
{
  if (dataStruct1.key1 != dataStruct2.key1)
  {
    return dataStruct1.key1 < dataStruct2.key1;
  }
  if (dataStruct1.key2 != dataStruct2.key2)
  {
    return dataStruct1.key2 < dataStruct2.key2;
  }
  return dataStruct1.str.length() < dataStruct2.str.length();
}

bool operator>(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept
{
  return operator<(dataStruct2, dataStruct1);
}

bool operator==(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept
{
  return ((dataStruct1.key1 == dataStruct2.key1) && (dataStruct1.key2 == dataStruct2.key2) 
        && (dataStruct1.str.length() == dataStruct2.str.length()));
}

bool operator<=(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept
{
  return ((dataStruct1 < dataStruct2) || (dataStruct1 == dataStruct2));
}

bool operator>=(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept
{
  return ((dataStruct1 > dataStruct2) || (dataStruct1 == dataStruct2));
}

void print(const DataStruct& dataStruct)
{
  std::cout << dataStruct;
}
