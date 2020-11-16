#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "parse.hpp"

std::string parseName(std::istream &sin)
{
  std::string name;
  getline(sin, name);
  if (name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  name.erase(0, 1);
  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  name.erase(std::remove(name.begin(), name.end(), '\\'), name.end());
  name.erase(0, 1);
  name.pop_back();
  return name;
}

std::string parseNumber(std::istream &sin)
{
  std::string number;
  sin >> number;
  if (number.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  for (auto &digit : number)
  {
    if (!std::isdigit(digit))
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
  return number;
}

std::string getCheckedBookmark(std::istream &sin)
{
  std::string bookmark;
  sin >> bookmark;
  if (bookmark.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  for (auto &ch : bookmark)
  {
    if (!std::isalnum(ch) && ch != '-')
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
  return bookmark;
}

bool isValidSteps(const std::string &steps)
{
  if (steps.empty())
  {
    return false;
  }
  auto iter = steps.begin();
  if(steps[0] == '+' || steps[0] == '-')
  {
    ++iter;
  }
  if (std::any_of(iter, steps.end(), [](int i){return !std::isdigit(i);}))
  {
    return false;
  }
  return true;
}

int stepsToInt(std::string steps)
{
  if (!isValidSteps(steps))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }
  int sign = 1;
  if (steps[0] == '-')
  {
    sign = -1;
    steps.erase(0, 1);
  }
  else if (steps[0] == '+')
  {
    steps.erase(0, 1);
  }
  return std::stoi(steps) * sign;
}
