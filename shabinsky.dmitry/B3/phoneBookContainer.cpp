#include <iostream>
#include "phoneBookContainer.hpp"

const std::string CURRENT_BOOKMARK = "current";
const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
const std::string EMPTY = "<EMPTY>\n";

PhoneBookContainer::PhoneBookContainer(std::unique_ptr<PhoneBook> &&book)
{
  book_ = std::move(book);
  bookmarks_[CURRENT_BOOKMARK] = book_->beginIt();
}

void PhoneBookContainer::add(const PhoneBook::Note &note)
{
  book_->pushBack(note);
  if (book_->size() == 1)
  {
    bookmarks_[CURRENT_BOOKMARK] = book_->beginIt();
  }
}

void PhoneBookContainer::insertBefore(const std::string &bookmark, const PhoneBook::Note &note)
{
  if (bookmark == CURRENT_BOOKMARK && book_->size() == 0)
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
  book_->insert(note, it->second);
  if (bookmarks_.size() == 1)
  {
    bookmarks_[CURRENT_BOOKMARK] = book_->beginIt();
  }
}

void PhoneBookContainer::insertAfter(const std::string &bookmark, const PhoneBook::Note &note)
{
  if (bookmark == CURRENT_BOOKMARK && book_->size() == 0)
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
  book_->insert(note, std::next(it->second));
  if (bookmarks_.size() == 1)
  {
    bookmarks_[CURRENT_BOOKMARK] = book_->beginIt();
  }
}

void PhoneBookContainer::removeNote(const std::string &bookmark)
{
  if (book_->size() == 0)
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
        if (std::next(mark.second) != book_->endIt())
        {
          mark.second = std::next(itRemove);
        }
        else
        {
          mark.second = book_->beginIt();
        }
      }
    }
    book_->removeAt(itRemove);
  }
}

void PhoneBookContainer::showNote(const std::string &bookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    std::cout << INVALID_BOOKMARK;
  }
  else if (book_->size() == 0)
  {
    std::cout << EMPTY;
  }
  else
  {
    return PhoneBookContainer::show(it->second);
  }
}

void PhoneBookContainer::storeBookmark(const std::string &bookmark, const std::string &bookmarkNew)
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

void PhoneBookContainer::moveBookmark(const std::string &bookmark, int steps)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    int counter = 0;
    if (steps > 0)
    {
      while (counter != steps && it->second != std::prev(book_->endIt()))
      {
        it->second = std::next(it->second);
        ++counter;
      }
    }
    else if (steps < 0)
    {
      while (counter != steps && it->second != book_->beginIt())
      {
        it->second = std::prev(it->second);
        --counter;
      }
    }
  }
  else
  {
    std::cout << INVALID_BOOKMARK;
  }
}

void PhoneBookContainer::moveBookmark(const std::string &bookmark, const PhoneBookContainer::MoveType moveType)
{
  auto it = bookmarks_.find(bookmark);
  if (it != bookmarks_.end())
  {
    if (moveType == MoveType::FIRST)
    {
      it->second = book_->beginIt();
    }
    else
    {
      it->second = std::prev(book_->endIt());
    }
  }
  else
  {
    std::cout << INVALID_BOOKMARK;
  }
}

void PhoneBookContainer::show(PhoneBook::Iterator it)
{
  std::cout << it->number_ << " " << it->name_ << "\n";
}
