#include <iostream>
#include <algorithm>
#include "isValidDate.hpp"

std::string checkNumber(std::istream& in)
{
  std::string number;
  in >> number;

  if (number.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }

  for (auto i : number)
  {
    if (!std::isdigit(i))
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
  return number;
}

std::string checkName(std::istream& in)
{
  std::string name;
  getline(in, name);

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

std::string checkBookmark(std::istream& in)
{
  std::string bookmark;
  in >> bookmark;

  if (bookmark.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }

  for (auto &i : bookmark)
  {
    if (!isalnum(i) && i != '-')
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }
  return bookmark;
}

bool checkStep(const std::string &step)
{
  if (step.empty())
  {
    return false;
  }

  if (std::any_of(step.begin(), step.end(), [](int i){return !std::isdigit(i);}))
  {
    return false;
  }

  return true;
}

int getStep(std::string step)
{

  int sign = 1;
  switch (step[0])
  {
    case '-':
      step.erase(step.begin());
      sign = -1;
      break;
    case '+':
      step.erase(step.begin());
      break;
  }

  if (!checkStep(step))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }

  return std::stoi(step) * sign;
}

