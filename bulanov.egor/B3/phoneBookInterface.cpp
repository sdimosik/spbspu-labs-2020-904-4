#include "phoneBookInterface.hpp"

PhoneBookInterface::PhoneBookInterface(std::unique_ptr<PhoneBook>&& phoneBook)
{
  phoneBook_ = std::move(phoneBook);
  bookmark_["current"] = phoneBook_->begin();
}

void PhoneBookInterface::executeAdd(const PhoneBook::Records &record)
{
  phoneBook_->pushBack(record);
  if (phoneBook_->begin() == --phoneBook_->end())
  {
    bookmark_["current"] = phoneBook_->begin();
  }
}

void PhoneBookInterface::executeStore(const std::string &bookmark, const std::string &newBookmark)
{
  auto iter = bookmark_.find(bookmark);
  if (iter != bookmark_.end())
  {
    bookmark_[newBookmark] = iter->second;
    return;
  }
  std::cout << "<INVALID BOOKMARK>" << '\n';
}


void PhoneBookInterface::executeInsertBefore(const std::string &bookmark, const PhoneBook::Records &record)
{
  if (bookmark == "current" && bookmark_[bookmark] == phoneBook_->end())
  {
    executeAdd(record);
    return;
  }

  auto iter = bookmark_.find(bookmark);

  if (iter != bookmark_.end())
  {
    if (iter != bookmark_.end())
    {
      phoneBook_->insertBefore(iter->second, record);
      if (bookmark_.size() == 1)
      {
        bookmark_["current"] = phoneBook_->begin();
      }
    }
    else
    {
      std::cout << "<INVALID BOOKMARK>" << '\n';
    }
  }
}

void PhoneBookInterface::executeInsertAfter(const std::string &bookmark, const PhoneBook::Records &record)
{
  if (bookmark == "current" && bookmark_[bookmark] == phoneBook_->end())
  {
    executeAdd(record);
    return;
  }

  auto iter = bookmark_.find(bookmark);

  if (iter != bookmark_.end())
  {
    if (iter != bookmark_.end())
    {
      phoneBook_->insertAfter(iter->second, record);
      if (bookmark_.size() == 1)
      {
        bookmark_["current"] = phoneBook_->begin();
      }
    }
    else
    {
      std::cout << "<INVALID BOOKMARK>" << '\n';
    }
  }
}

void PhoneBookInterface::executeRemove(const std::string &bookmark)
{
  auto iter = bookmark_.find(bookmark);
  if (iter == bookmark_.end())
  {
    std::cout << "<INVALID BOOKMARK>" << '\n';
    return;
  }
  if (iter->second != phoneBook_->end())
  {
    auto removeIt = iter->second;

    for (auto i = bookmark_.begin(); i != bookmark_.end(); i++)
    {
      if (i->second == removeIt)
      {
        if (std::next(i->second) != phoneBook_->end())
        {
          i->second = std::next(removeIt);
        }
        else
        {
          i->second = std::prev(removeIt);
        }
      }
    }
    phoneBook_->erase(removeIt);
  }
}

void PhoneBookInterface::executeShow(const std::string &bookmark)
{
  auto iter = bookmark_.find(bookmark);
  if (iter == bookmark_.end())
  {
    std::cout << "<INVALID BOOKMARK>" << '\n';
    return;
  }
  if (iter->second == phoneBook_->end())
  {
    std::cout << "<EMPTY>" << '\n';
    return;
  }
  return phoneBook_->showThisRecord(iter->second);
}

void PhoneBookInterface::executeMove(const std::string &bookmark, const int step)
{
  auto iter = bookmark_.find(bookmark);
  if (iter != bookmark_.end())
  {
    std::advance(iter->second, step);
    return;
  }
  std::cout << "<INVALID BOOKMARK>" << '\n';
}

void PhoneBookInterface::executeMove(const std::string &bookmark, const MovePosition &position)
{
  auto iter = bookmark_.find(bookmark);
  if (iter != bookmark_.end())
  {
    switch (position)
    {
      case MovePosition::FIRST:
      {
        iter->second = phoneBook_->begin();
        break;
      }
      case MovePosition::LAST:
      {
        iter->second = std::prev(phoneBook_->end());
        break;
      }
    }
    return;
  }
  std::cout << "<INVALID BOOKMARK>" << '\n';
}
