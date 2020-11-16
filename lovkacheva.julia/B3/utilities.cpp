#include "utilities.hpp"

bool lovkacheva::isABookmarkName(const std::string& bookmarkName)
{
  for (char character : bookmarkName)
  {
    if (!isalpha(character) && !isdigit(character) && (character != '-'))
    {
      return false;
    }
  }
  return true;
}

bool lovkacheva::isAPhoneNumber(const std::string& number)
{
  for (char character : number)
  {
    if (!isdigit(character))
    {
      return false;
    }
  }
  return true;
}

void lovkacheva::processName(std::string& name)
{
  if (name.back() == '"' && name.front() == '"')
  {
    name.erase(name.begin());
    name.erase(std::prev(name.end()));
    for (std::string::iterator i = name.begin(); i != name.end(); i++)
    {
      if (*i == '\\')
      {
        std::string::iterator iNext = std::next(i);
        if (iNext != name.end() && (*iNext == '\\' || *iNext == '"'))
        {
          i = name.erase(i);
        }
        else
        {
          name.clear();
          break;
        }
      }
      else if (*i == '"')
      {
        name.clear();
        break;
      }
    }
  }
  else
  {
    name.clear();
  }
}
