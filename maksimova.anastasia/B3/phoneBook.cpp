#include <iostream>
#include "phoneBook.hpp"

phoneBook::iterator phoneBook::begin() noexcept
{
  return list_.begin();
}

phoneBook::iterator phoneBook::end() noexcept
{
  return list_.end();
}

void phoneBook::insertAfter(const std::string &number, const std::string &name, iterator iter)
{
  list_.insert(++iter, {number, name});
}

void phoneBook::insertBefore(const std::string &number, const std::string &name, iterator iter)
{
  list_.insert(iter, {number, name});
}

void phoneBook::pushBack(const std::string &number, const std::string &name)
{
  list_.push_back({number, name});
}

void phoneBook::eraseNote(iterator iter)
{
  list_.erase(iter);
}

void phoneBook::replace(const std::string &name, const std::string &number, iterator iter)
{
  iter->number = number;
  iter->name = name;
}

phoneBook::iterator phoneBook::move(iterator iter, const int steps)
{
  int count = steps;
  if(count >= 0)
  {
    while (count != 0)
    {
      if (iter != std::prev(list_.end()))
      {
        ++iter;
        --count;
      }
      else
      {
        iter = list_.begin();
        --count;
      }
    }
  }
  else if (count < 0)
  {
    while (count != 0)
    {
      if (iter != list_.begin())
      {
        --iter;
        ++count;
      }
      else
      {
        iter = std::prev(list_.end());
        ++count;
      }
    }
  }
  return iter;
}

void phoneBook::showCurrent(std::ostream &out, iterator iter) const
{
  out << iter->number << ' ' << iter->name << '\n';
}
