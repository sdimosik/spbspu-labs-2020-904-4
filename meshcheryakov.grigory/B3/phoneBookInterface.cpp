#include "phoneBookInterface.hpp"
#include <algorithm>

PhoneBookInterface::PhoneBookInterface(std::unique_ptr<PhoneBook> &&phoneBook)
{
  phoneBook_ = std::move(phoneBook);
  bookmarks_["current"] = phoneBook_->begin();
}

void PhoneBookInterface::add(const PhoneBook::PhoneBookNote &note)
{
  phoneBook_->pushBack(note);
  if (phoneBook_->begin() == --phoneBook_->end())
  {
    bookmarks_["current"] = phoneBook_->begin();
  }
}

void PhoneBookInterface::store(const std::string &bookmark, const std::string &newBookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    bookmarks_[newBookmark] = it->second;
  } else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::insertAfter(const std::string &bookmark, const PhoneBook::PhoneBookNote &note)
{
  if (bookmark == "current" && bookmarks_[bookmark] == phoneBook_->end())
  {
    add(note);
    return;
  }
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    phoneBook_->insertAfter(it->second, note);
    if (bookmarks_.size() == 1)
    {
      bookmarks_["current"] = phoneBook_->begin();
    }
  } else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::insertBefore(const std::string &bookmark, const PhoneBook::PhoneBookNote &note)
{
  if (bookmark == "current" && bookmarks_[bookmark] == phoneBook_->end())
  {
    add(note);
    return;
  }
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    phoneBook_->insertBefore(it->second, note);
    if (bookmarks_.size() == 1)
    {
      bookmarks_["current"] = phoneBook_->begin();
    }
  } else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::deleteBookmarkNote(const std::string &bookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  if (it->second != phoneBook_->end())
  {
    auto deleteIt = it->second;
    for (auto &mark : bookmarks_)
    {
      if (mark.second == deleteIt)
      {
        if (std::next(mark.second) != phoneBook_->end())
        {
          mark.second = std::next(deleteIt);
        }
        else
        {
          mark.second = std::prev(deleteIt);
        }
      }
    }
    phoneBook_->deleteBookmark(deleteIt);
  }
}


void PhoneBookInterface::showBookmark(const std::string &bookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  if (it->second == phoneBook_->end())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  return phoneBook_->show(it->second);
}

void PhoneBookInterface::moveBookmark(const std::string &bookmark, const int step)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    it->second = phoneBook_->move(it->second, step);
  } else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }

}

void PhoneBookInterface::moveBookmark(const std::string &bookmark, const MovePosition &pos)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    if (pos == MovePosition::FIRST)
    {
      it->second = phoneBook_->begin();
    } else
    {
      it->second = phoneBook_->prev(phoneBook_->end());
    }
  } else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}
