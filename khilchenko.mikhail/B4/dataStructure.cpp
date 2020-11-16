#include <string>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "dataStructure.hpp"

const int minNumber = -5;
const int maxNumber = 5;

bool isNumberCorrect(const int number)
{
  return((number >= minNumber) && (number <= maxNumber));
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

std::istream& operator>>(std::istream& sin, DataStructure& data)
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
    throw std::invalid_argument("Invalid input(missing comma)");
  }
  comma = '\0';
  in >> key2 >> comma;
  if(comma != ',')
  {
    throw std::invalid_argument("Invalid input(missing comma)");
  }
  std::getline(in >> std::ws, inputString);
  if(!in.eof() && in.fail())
  {
    throw std::runtime_error("Error in reading data");
  }
  if(!isNumberCorrect(key1) || !isNumberCorrect(key2) || inputString.empty())
  {
    throw std::invalid_argument("Invalid input");
  }
  data.key1 = key1;
  data.key2 = key2;
  data.str = inputString;
  return sin;
}

std::ostream& operator<<(std::ostream& out, const DataStructure& data)
{
  out << data.key1 << ',' << data.key2 << ',' << data.str << '\n';
  return out;
}
