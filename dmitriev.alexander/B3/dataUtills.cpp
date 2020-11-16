#include "dataUtills.hpp"

bool refactorAndCheckName(std::string &name)
{
  if (name.empty() || name.front() != '\"' || name.back() != '\"')
  {
    return false;
  }
  name.erase(name.begin());
  name.erase(--name.end());

  size_t digitIndex = 0;
  while (digitIndex < name.size())
  {
    if (name[digitIndex] == '\\')
    {
      name.erase(digitIndex, 1);
    }
    digitIndex++;
  }

  return !name.empty();
}

bool isNumberValid(const std::string &number)
{
  for (auto &digit: number)
  {
    if (!std::isdigit(digit))
    {
      return false;
    }
  }
  return !number.empty();
}

bool isBookmarkValid(const std::string &bookmark)
{
  for (auto &symbol: bookmark)
  {
    if (!isalnum(symbol) && (symbol != '-'))
    {
      return false;
    }
  }
  return !bookmark.empty();
}
