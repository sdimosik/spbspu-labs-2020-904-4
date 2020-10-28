#include <iostream>
#include "phoneBookContainer.hpp"

const std::string CURRENT_BOOKMARK = "current";
const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
const std::string EMPTY = "<EMPTY>\n";

phoneBookContainer::phoneBookContainer()
{
  bookmarks_[CURRENT_BOOKMARK] = book_.begin();
}

void phoneBookContainer::add(const PhoneBook::Note &note)
{
  book_.push_back(note);
  if (book_.size() == 1)
  {
    bookmarks_[CURRENT_BOOKMARK] = book_.begin();
  }
}

void phoneBookContainer::insert(const std::string &bookmark, const phoneBookContainer::InsertType &insertType,
                                const PhoneBook::Note &note)
{
  if (bookmark == CURRENT_BOOKMARK && book_.size() == 0)
  {
    add(note);
    return;
  }
  
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
    return;
  }
  it->second = book_.insert(note, insertType, it->second);
}

void phoneBookContainer::removeNote(const std::string &bookmark)
{
  if (book_.size() == 0)
  {
    std::cout << EMPTY;
    return;
  }
  
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
  }
  else
  {
    auto itRemove = it->second;
    for (auto &mark : bookmarks_)
    {
      if (mark.second == itRemove)
      {
        if (std::next(mark.second) != book_.end())
        {
          mark.second = std::next(itRemove);
        }
        else
        {
          mark.second = book_.begin();
        }
      }
    }
    book_.remove(itRemove);
  }
}

void phoneBookContainer::showNote(const std::string &bookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
  }
  else if (book_.size() == 0)
  {
    std::cout << EMPTY;
  }
  else
  {
    return book_.show(it->second);
  }
}

void phoneBookContainer::storeBookmark(const std::string &bookmark, const std::string &bookmarkNew)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    bookmarks_[bookmarkNew] = it->second;
  }
  else
  {
    std::cout << INVALID_BOOKMARK;
  }
}

void phoneBookContainer::moveBookmark(const std::string &bookmark, int steps)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    it->second = book_.move(steps, it->second);
  }
  else
  {
    std::cout << INVALID_BOOKMARK;
  }
}

void phoneBookContainer::moveBookmark(const std::string &bookmark, const phoneBookContainer::MoveType &moveType)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    if (moveType == MoveType::FIRST)
    {
      it->second = book_.begin();
    }
    else
    {
      it->second = std::prev(book_.end());
    }
  }
  else
  {
    std::cout << INVALID_BOOKMARK;
  }
}
