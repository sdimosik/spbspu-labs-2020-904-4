#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "dataStruct.hpp"

bool cmp(DataStruct& data1, DataStruct& data2)
{
  if (data1.key1 != data2.key1)
  {
    return (data1.key1 < data2.key1);
  }
  if (data1.key2 != data2.key2)
  {
    return (data1.key2 < data2.key2);
  }
  return (data1.str.size() < data2.str.size());
}

bool isNumberValid(const int number)
{
  return ((number >= MIN_KEY) && (number <= MAX_KEY));
}

std::istream& inString(std::istream& in)
{
  if (in.peek() == '\n')
  {
    in.clear();
    in.setstate(std::ios_base::failbit);
    return in;
  }
  while (isspace(in.peek()))
  {
    in.ignore(1);
    if (in.peek() == '\n')
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
  in >> key;
  if (!isNumberValid(key) || (in.peek() != ','))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  data.key1 = key;
  in.ignore(1);
  in >> inString >> key >> inString;
  if (!isNumberValid(key) || (in.peek() != ','))
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  data.key2 = key;
  in.ignore(1);
  std::string temp;
  getline(in, temp);
  data.str = temp;
  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct)
{
  out << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str;
  return out;
}

void task()
{
  std::vector<DataStruct> vec((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());
  if ((!std::cin.eof()) && (std::cin.fail()))
  {
    throw std::ios_base::failure("Error by reading data!\n");
  }
  std::sort(vec.begin(), vec.end(), cmp);
  std::copy(vec.begin(), vec.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
}
