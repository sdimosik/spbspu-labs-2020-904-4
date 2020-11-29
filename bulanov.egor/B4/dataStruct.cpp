#include "dataStruct.hpp"
#include <iostream>

const int KEY_MIN = -5;
const int KEY_MAX = 5;

bool isNumberValid(const int number)
{
  return((number >= KEY_MIN) && (number <= KEY_MAX));
}

bool DataStruct::operator<(const DataStruct &data) const
{
  if(key1 == data.key1)
  {
    if(key2 == data.key2)
    {
      return (str.length() < data.str.length());
    }
    return (key2 < data.key2);
  }
  return (key1 < data.key1);
}

std::ostream& operator<<(std::ostream& out, const DataStruct& data)
{
  return (out << data.key1 << ',' << data.key2 << ',' << data.str);
}

std::istream& inString(std::istream& in)
{
  if(in.peek() == '\n')
  {
    in.clear();
    in.setstate(std::ios_base::failbit);
    return in;
  }

  while(isspace(in.peek()))
  {
    in.ignore(1);
    if(in.peek() == '\n')
    {
      in.clear();
      in.setstate(std::ios_base::failbit);
      return in;
    }
  }

  return in;
}

std::istream& operator>>(std::istream& in, DataStruct& data)
{
  if (in.peek() == std::char_traits<char>::eof())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  int key;
  in >> key >> inString;
  if (!isNumberValid(key))
  {
    throw std::invalid_argument("Error: key 1 is out of range!");
  }
  data.key1 = key;
  if (in.peek() != ',')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.ignore(1);

  in >> inString >> key >> inString;
  if (!isNumberValid(key))
  {
    throw std::invalid_argument("Error: key 2 is out of range!");
  }
  if(in.peek() != ',')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.ignore(1);
  data.key2 = key;

  std::string inputStr;
  getline(in, inputStr);
  if (inputStr.empty())
  {
    throw std::invalid_argument("Error: string is empty!");
  }
  data.str = inputStr;

  return in;
}

