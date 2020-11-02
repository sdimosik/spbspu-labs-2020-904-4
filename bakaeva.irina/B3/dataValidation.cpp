#include <iostream>
#include <algorithm>

std::string getCheckedName(std::istream & sin)
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

std::string getCheckedNumber(std::istream & sin)
{
  std::string number;
  sin >> number;

  if (number.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }

  for (auto &digit: number)
  {
    if (!std::isdigit(digit))
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }

  return number;
}

std::string getCheckedBookmark(std::istream & sin)
{
  std::string bookmark;
  sin >> bookmark;

  if (bookmark.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }

  for (auto &symbol: bookmark)
  {
    if (!isalnum(symbol) && (symbol != '-'))
    {
      throw std::invalid_argument("<INVALID COMMAND>\n");
    }
  }

  return bookmark;
}

bool checkSteps(const std::string &steps)
{
  if (steps.empty())
  {
    return false;
  }

  if (std::any_of(steps.begin(), steps.end(), [](int i){return !std::isdigit(i);}))
  {
    return false;
  }

  return true;
}

int getSteps(std::string steps)
{

  int sign = 1;
  switch (steps[0])
  {
    case '-':
      steps.erase(steps.begin());
      sign = -1;
      break;
    case '+':
      steps.erase(steps.begin());
      break;
  }

  if (!checkSteps(steps))
  {
    throw std::invalid_argument("<INVALID COMMAND>\n");
  }

  return std::stoi(steps) * sign;
}
