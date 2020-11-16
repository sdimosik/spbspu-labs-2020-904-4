#include "phoneBookInterface.hpp"
#include <algorithm>

PhoneBookInterface::PhoneBookInterface(std::unique_ptr<PhoneBook> &&phoneBook)
{
  phoneBook_ = std::move(phoneBook);
  bookmarks_["current"] = phoneBook_->begin();
}

void PhoneBookInterface::addNote(const PhoneBook::Note &note)
{
  phoneBook_->pushBack(note);
  if (phoneBook_->begin() == --phoneBook_->end())
  {
    bookmarks_["current"] = phoneBook_->begin();
  }
}

void PhoneBookInterface::storeBookmark(const std::string &bookmark, const std::string &newBookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    bookmarks_[newBookmark] = it->second;
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::insertNoteBefore(const std::string &bookmark, const PhoneBook::Note &note)
{
  if (bookmark == "current" && bookmarks_[bookmark] == phoneBook_->end())
  {
    addNote(note);
    return;
  }

  auto it = bookmarks_.find(bookmark);

  if (it != bookmarks_.end())
  {
    phoneBook_->insertNoteBefore(it->second, note);
    if (bookmarks_.size() == 1)
    {
      bookmarks_["current"] = phoneBook_->begin();
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::insertNoteAfter(const std::string &bookmark, const PhoneBook::Note &note)
{
  if (bookmark == "current" && bookmarks_[bookmark] == phoneBook_->end())
  {
    addNote(note);
    return;
  }

  auto it = bookmarks_.find(bookmark);

  if (it != bookmarks_.end())
  {
    phoneBook_->insertNoteAfter(it->second, note);
    if (bookmarks_.size() == 1)
    {
      bookmarks_["current"] = phoneBook_->begin();
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::eraseNote(const std::string &bookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  if (it->second != phoneBook_->end())
  {
    auto eraseIt = it->second;
    for (auto &mark : bookmarks_)
    {
      if (mark.second == eraseIt)
      {
        if (std::next(mark.second) != phoneBook_->end())
        {
          mark.second = std::next(eraseIt);
        }
        else
        {
          mark.second = std::prev(eraseIt);
        }
      }
    }
    phoneBook_->erase(eraseIt);
  }
}

void PhoneBookInterface::showNote(const std::string &bookmark)
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

  return phoneBook_->showNote(it->second);
}

void PhoneBookInterface::moveBookmark(const std::string &bookmark, const int steps)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    it->second = phoneBook_->move(it->second, steps);
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void PhoneBookInterface::moveBookmark(const std::string &bookmark, const MovePosition &position)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    switch (position)
    {
      case MovePosition::FIRST:
        it->second = phoneBook_->begin();
        break;
      case MovePosition::LAST:
        it->second = phoneBook_->prev(phoneBook_->end());
        break;
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}
