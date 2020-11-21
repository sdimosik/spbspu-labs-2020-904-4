#include "map_function.hpp"
#include <algorithm>

void add(map& mark, phoneBook& book, const phoneBook::contact_str &contact)
{
  book.push_back(contact);
  if(std::next(book.begin()) == book.end())
  {
    mark["current"] = book.begin();
  }
}

void store(map& mark, const std::string &mark_name, const std::string &new_mark_name)
{

  mark.emplace(new_mark_name, get_iterator(mark, mark_name)->second);
}

void insert(map& mark, const std::string &mark_name, phoneBook& book, const phoneBook::contact_str &contact,
            insertPos position)
{
  if((std::next(get_iterator(mark, mark_name)->second) == book.end() && position == AFTER) || book.empty())
  {
    add(mark,book, contact);
  }
  auto iter = get_iterator(mark, mark_name)->second;
  (position == BEFORE)? book.insert(iter, contact) : book.insert(std::next(iter), contact);
}

void remove(map& mark, const std::string &mark_name, phoneBook& book)
{
  auto iter = get_iterator(mark, mark_name);
  if(std::next(iter->second) != book.end())
  {
    std::for_each(mark.begin(), mark.end(),
                  [&](auto& mark)
                  {
                    if(mark.second == iter->second && mark.first != iter->first)
                    {
                      mark.second = std::next(iter->second);
                    }
                  });
    iter->second = book.erase(iter->second);
  }
  else
  {
    std::for_each(mark.begin(), mark.end(),
                  [&](auto& mark)
                  {
                    if(mark.second == iter->second && mark.first != iter->first)
                    {
                      mark.second = book.begin();
                    }
                  });
    book.erase(iter->second);
    iter->second = book.begin();
  }
}

void show(map& mark, const std::string &mark_name, std::ostream &out)
{
  auto iter = get_iterator(mark, mark_name);
  out << iter->second->number << " "
      << iter->second->name << '\n';
}

void move(map& mark, const std::string &mark_name, int steps)
{
  std::advance(get_iterator(mark, mark_name)->second, steps);
}

void move(map& mark, const std::string &mark_name, phoneBook& book, movePos position)
{
  auto iter = get_iterator(mark, mark_name);
  (position == FIRST)? iter->second = book.begin() : iter->second = std::prev(book.end());
}

void move_next(map& mark, const std::string &mark_name)
{
  move(mark, mark_name, +1);
}

void move_prev(map& mark, const std::string &mark_name)
{
  move(mark, mark_name, -1);
}

void replace(map& mark, const std::string &mark_name, const phoneBook::contact_str &contact)
{
  auto iter = get_iterator(mark, mark_name);
  *(iter->second) = contact;
}

bool is_exist(map& mark, const std::string &mark_name)
{
  for(const auto & i : mark)
  {
    if(i.first == mark_name)
    {
      return true;
    }
  }
  return false;
}

bool is_correct(map& mark, const std::string &mark_name, phoneBook& book)
{
  return get_iterator(mark, mark_name)->second != book.end();
}

std::map<std::string, phoneBook::iterator>::iterator get_iterator(map& mark, const std::string &mark_name)
{
  for(auto iter = mark.begin(); iter != mark.end(); iter++)
  {
    if(iter->first == mark_name)
    {
      return iter;
    }
  }

  throw std::invalid_argument(" can't get non-existent mark! \n ");
}


