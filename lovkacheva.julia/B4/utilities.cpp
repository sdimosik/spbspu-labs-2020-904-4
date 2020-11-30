#include "utilities.hpp"
#include <string>
#include <iostream>
#include <sstream>

using DataStruct = lovkacheva::DataStruct;

int lovkacheva::parseKey(const std::string& key)
{
  if (key.empty())
  {
    throw std::invalid_argument("The key must not be empty");
  }
  const char last = key.back();
  const size_t size = key.size();
  if ( last <= '5' && last >= '0' && (size == 1 || (size == 2 && key[0] == '-')))
  {
    return stoi(key);
  }
  else
  {
    throw std::invalid_argument("The key must be a number within range [-5,5], " + key + " isn't");
  }
  
}

int lovkacheva::readKey(std::istream &in)
{
  in >> std::ws;
  std::string key;
  getline(in, key, ',');
  if (in)
  {
    return parseKey(key);
  }
  else
  {
    throw std::runtime_error("Invalid input");
  }
}

void lovkacheva::skipNonNewlineWs(std::istream &in)
{
  char next = in.peek();
  while (isspace(next))
  {
    if (next == '\n')
    {
      throw std::runtime_error("Invalid input: no newlines between data allowed");
    }
    in.get();
    next = in.peek();
  }
}

void lovkacheva::readStructs(std::istream &in, std::vector<DataStruct> &dataVector)
{
  while (in.peek() != EOF)
  {
    int firstKey = readKey(in);
    skipNonNewlineWs(in);
    dataVector.push_back({firstKey, readKey(in)});
    skipNonNewlineWs(in);
    getline(in, dataVector.back().str);
    if (dataVector.back().str.empty())
    {
      throw std::runtime_error("Invalid input: str must not be empty");
    }
    if (in.fail() && !in.eof())
    {
      throw std::runtime_error("Input error");
    }
  }
}

bool lovkacheva::less(const DataStruct &first, const DataStruct &second)
{
  if (first.key1 < second.key1)
  {
    return true;
  }
  else if (first.key1 == second.key1)
  {
    if (first.key2 < second.key2)
    {
      return true;
    }
    else if (first.key2 == second.key2)
    {
      return first.str.length() < second.str.length();
    }
  }
  return false;
}
