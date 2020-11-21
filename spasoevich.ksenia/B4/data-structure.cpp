#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "data-structure.hpp"

bool isNumberInCorrectRange(const int number)
{
  return((number >= LOWER_LIMIT) && (number <= UPPER_LIMIT));
}

bool operator<(const DataStructure& first, const DataStructure& second)
{
  if(first.key1 == second.key1)
  {
    if(first.key2 == second.key2)
    {
      return first.str.size() < second.str.size();
    }
    return first.key2 < second.key2;
  }
  return first.key1 < second.key1;
}

std::istream& operator>>(std::istream& sin, DataStructure& dataStruct)
{
  std::string string;
  if(!getline(sin, string))
  {
    return sin;
  }
  std::istringstream in(string);
  int key1, key2;
  std::string inputString;
  char comma = '\0';
  in >> key1 >> comma;
  if(comma != ',')
  {
    throw std::invalid_argument("Comma is missing!");
  }
  comma = '\0';
  in >> key2 >> comma;
  if(comma != ',')
  {
    throw std::invalid_argument("Comma is missing!");
  }
  std::getline(in >> std::ws, inputString);
  if(!in.eof() && in.fail())
  {
    throw std::runtime_error("Error while reading data!");
  }
  if(!isNumberInCorrectRange(key1) || !isNumberInCorrectRange(key2) || inputString.empty())
  {
    throw std::out_of_range("Keys are out of range!");
  }
  dataStruct.key1 = key1;
  dataStruct.key2 = key2;
  dataStruct.str = inputString;
  return sin;
}

std::ostream& operator<<(std::ostream& out, const DataStructure& dataStruct)
{
  out << dataStruct.key1 << ',' << dataStruct.key2 << ',' << dataStruct.str << '\n';
  return out;
}

