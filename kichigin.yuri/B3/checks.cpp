#include "checks.hpp"

std::string checkName(const std::string& name)
{
  std::string newName(name);
  if (newName.empty() || newName.front() != '\"' || newName.back() != '\"')
  {
    return "";
  }
  newName.erase(newName.begin());
  newName.erase(--newName.end());

  for (size_t i = 0; i < newName.size(); i++)
  {
    if (newName[i] == '\\')
    {
      newName.erase(i, 1);
    }
  }

  if (newName.empty())
  {
    return "";
  }

  return newName;
}

std::string checkNumber(const std::string& number)
{
  if (number.empty())
  {
    return "";
  }

  for (auto& digit : number)
  {
    if (!std::isdigit(digit))
    {
      return "";
    }
  }

  return number;
}

std::string checkBookmark(const std::string& bookmark)
{
  if (bookmark.empty())
  {
    return "";
  }

  for (auto& symbol : bookmark)
  {
    if (!isalnum(symbol) && symbol != '-')
    {
      return "";
    }
  }
  return bookmark;
}
