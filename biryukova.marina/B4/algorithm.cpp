#include "algorithm.hpp"
#include <stdexcept>
#include <vector>
#include <iostream>
#include <sstream>
#include <algorithm>

bool testValidKey(const int key)
{
  return ((key >= MIN_KEY) && (key <= MAX_KEY));
}

bool testValidInput(std::string& input)
{
  int commasNumber = 0;
  for (size_t i = 0; i < input.size(); i++)
  {
    if (input[i] == ',')
    {
      commasNumber++;
    }
  }
  if (commasNumber == COMMAS_NUMBER)
  {
    return true;
  }
  return false;
}

DataStruct getDataStruct(std::string& line)
{
  if (!testValidInput(line))
  {
    throw std::invalid_argument("Invalid input");
  }
  std::istringstream input(line);
  int key1, key2;
  char comma;
  std::string str;
  input >> key1 >> comma >> key2 >> comma >> str;
  if (!input.eof())
  {
    std::string temp;
    getline(input, temp);
    str += temp;
  }
  if (input.fail() && !input.eof())
  {
    throw std::runtime_error("Error while reading");
  }
  if (!testValidKey(key1) || !testValidKey(key2))
  {
    throw std::invalid_argument("Invalid key");
  }
  return DataStruct{key1, key2, str};
}

void printVector(std::vector<DataStruct>& array)
{
  std::vector<DataStruct>::iterator iter = array.begin();
  while (iter != array.end())
  {
    std::cout << iter->key1 << "," << iter->key2 << "," << iter->str << '\n';
    iter++;
  }
}

bool comparator(DataStruct& lhs, DataStruct& rhs)
{
  if (lhs.key1 != rhs.key1)
  {
    return (lhs.key1 < rhs.key1);
  }
  if (lhs.key2 != rhs.key2)
  {
    return (lhs.key2 < rhs.key2);
  }
  if (lhs.str.size() != rhs.str.size())
  {
    return (lhs.str.size() < rhs.str.size());
  }
  return (lhs.str < rhs.str);
}

void algorithm()
{
  std::vector<DataStruct> array;
  std::string input;
  while (std::getline(std::cin, input))
  {
    array.push_back(getDataStruct(input));
  }
  std::sort(array.begin(), array.end(), comparator);
  printVector(array);
}
