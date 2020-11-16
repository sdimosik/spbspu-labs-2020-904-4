#include <istream>
#include <sstream>
#include "dataStruct.hpp"

const char DELIMITER = ',';
const int MIN_KEY_VALUE = -5;
const int MAX_KEY_VALUE = 5;

bool isValidRange(int key)
{
  if (key < MIN_KEY_VALUE || key > MAX_KEY_VALUE)
  {
    return false;
  }
  return true;
}

int readKey(std::istream &in)
{
  int key;
  in >> key >> std::ws;
  if (in.get() != DELIMITER || !isValidRange(key))
  {
    throw std::invalid_argument("");
  }
  return key;
}

std::istream &operator>>(std::istream &in, DataStruct &data)
{
  try
  {
    std::string token;
    getline(in, token);
    std::stringstream sin(token);
    
    data.key1 = readKey(sin);
    token.clear();
    
    data.key2 = readKey(sin);
    token.clear();
    
    getline(sin, token);
    if (token.empty())
    {
      data.str = "";
    }
    else
    {
      data.str = token;
    }
    if (data.str.empty())
    {
      throw std::invalid_argument("");
    }
  }
  catch (std::exception &e)
  {
    in.setstate(std::ios_base::failbit);
  }
  return in;
}

std::ostream &operator<<(std::ostream &out, const DataStruct &data)
{
  out << data.key1 << DELIMITER << data.key2 << DELIMITER << data.str;
  return out;
}

bool operator<(const DataStruct &data1, const DataStruct &data2)
{
  if (data1.key1 == data2.key1 && data1.key2 == data2.key2)
  {
    return (data1.str.length() < data2.str.length());
  }
  else if (data1.key1 == data2.key1)
  {
    return (data1.key2 < data2.key2);
  }
  else
  {
    return (data1.key1 < data2.key1);
  }
}
