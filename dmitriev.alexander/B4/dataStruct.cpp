#include "dataStruct.hpp"
#include <string>
#include <stdexcept>
#include <sstream>

const char DELIMITER = ',';
const int MIN_NUMBER = -5;
const int MAX_NUMBER = 5;

int readKey(std::istream &sin)
{
  int key;
  sin >> key;
  sin >> std::ws;
  if (sin.get() != DELIMITER)
  {
    throw std::invalid_argument("");
  }
  if (key < MIN_NUMBER || key > MAX_NUMBER)
  {
    throw std::invalid_argument("");
  }
  return key;
}

std::istream &operator>>(std::istream &cin, DataStruct &dataStruct)
{
  try
  {
    std::string token;
    getline(cin, token);
    std::stringstream sin(token);

    dataStruct.key1 = readKey(sin);
    token.clear();

    dataStruct.key2 = readKey(sin);
    token.clear();

    getline(sin, token);
    if (token.empty())
    {
      dataStruct.str = "";
    } else
    {
      dataStruct.str = token;
    }
    if (dataStruct.str.empty())
    {
      throw std::invalid_argument("");
    }
  }
  catch (std::exception &e)
  {
    cin.setstate(std::ios_base::failbit);
  }
  return cin;
}

std::ostream &operator<<(std::ostream &ostream, const DataStruct &dataStruct)
{
  ostream << dataStruct.key1 << DELIMITER << dataStruct.key2 << DELIMITER << dataStruct.str;
  return ostream;
}

bool operator<(const DataStruct &lhs, const DataStruct &rhs)
{
  if (lhs.key1 == rhs.key1 && lhs.key2 == rhs.key2)
  {
    return (lhs.str.length() < rhs.str.length());
  } else if (lhs.key1 == rhs.key1)
  {
    return (lhs.key2 < rhs.key2);
  } else
  {
    return (lhs.key1 < rhs.key1);
  }
}
