#include "phoneBookContainer.hpp"

const std::string CURRENT_BOOKMARK = "current";
const std::string INVALID_BOOKMARK = "<INVALID BOOKMARK>\n";
const std::string EMPTY = "<EMPTY>\n";

PhoneBookContainer::PhoneBookContainer(std::unique_ptr<PhoneBook> &&book)
{
  book_ = std::move(book);
  bookmarksMap_[CURRENT_BOOKMARK] = book_->beginIter();
}

void PhoneBookContainer::showNote(const PhoneBook::iterator it)
{
  std::cout << it->number_ << " " << it->name_ << "\n";
}

void PhoneBookContainer::addNote(const PhoneBook::Note &note)
{
  book_->pushBack(note);
  if (book_->size() == 1)
  {
    bookmarksMap_[CURRENT_BOOKMARK] = book_->beginIter();
  }
}

void PhoneBookContainer::insertNoteBefore(const std::string &bookmark, const PhoneBook::Note &note)
{
  if (bookmark == CURRENT_BOOKMARK && book_->size() == 0)
  {
    addNote(note);
    return;
  }

  const auto foundBookmark = bookmarksMap_.find(bookmark);
  insertNote(foundBookmark->second, foundBookmark, note);
}

void PhoneBookContainer::insertNoteAfter(const std::string &bookmark, const PhoneBook::Note &note)
{
  if (bookmark == CURRENT_BOOKMARK && book_->size() == 0)
  {
    addNote(note);
    return;
  }

  const auto foundBookmark = bookmarksMap_.find(bookmark);
  insertNote(std::next(foundBookmark->second), foundBookmark, note);
}

void PhoneBookContainer::insertNote(PhoneBook::iterator insertPos,
  std::map<std::string, PhoneBook::iterator>::const_iterator foundBookmark,
  const PhoneBook::Note &note)
{
  if (foundBookmark != bookmarksMap_.end())
  {
    book_->insertNote(insertPos, note);
    if (bookmarksMap_.size() == 1)
    {
      bookmarksMap_[CURRENT_BOOKMARK] = book_->beginIter();
    }
  } else
  {
    std::cout << INVALID_BOOKMARK;
  }
}

void PhoneBookContainer::removeNote(const std::string &bookmarkToRemove)
{
  if (book_->size() == 0)
  {
    std::cout << EMPTY;
    return;
  }

  const auto foundBookmark = bookmarksMap_.find(bookmarkToRemove);
  if (foundBookmark == bookmarksMap_.end())
  {
    std::cout << INVALID_BOOKMARK;
  } else if (foundBookmark != bookmarksMap_.end())
  {
    const auto posToRemove = foundBookmark->second;
    for (auto &bookmark : bookmarksMap_)
    {
      if (bookmark.second == posToRemove)
      {
        if (std::next(bookmark.second) != book_->endIter())
        {
          bookmark.second = std::next(posToRemove);
        } else
        {
          bookmark.second = book_->beginIter();
        }
      }
    }
    book_->removeAt(posToRemove);
  }
}

void PhoneBookContainer::showNote(const std::string &bookmark)
{
  const auto foundBookmark = bookmarksMap_.find(bookmark);
  if (foundBookmark == bookmarksMap_.end())
  {
    std::cout << INVALID_BOOKMARK;
  } else if (book_->size() == 0)
  {
    std::cout << EMPTY;
  } else
  {
    return PhoneBookContainer::showNote(foundBookmark->second);
  }
}

void PhoneBookContainer::storeBookmark(const std::string &bookmark, const std::string &newBookmark)
{
  auto foundBookmark = bookmarksMap_.find(bookmark);
  if (foundBookmark != bookmarksMap_.end())
  {
    bookmarksMap_[newBookmark] = foundBookmark->second;
  } else
  {
    std::cout << INVALID_BOOKMARK;
  }
}

void PhoneBookContainer::moveBookmark(const std::string &bookmark, int steps)
{
  const auto foundBookmark = bookmarksMap_.find(bookmark);
  if (foundBookmark != bookmarksMap_.end())
  {
    int counter = 0;
    if (steps > 0)
    {
      while (counter != steps && foundBookmark->second != std::prev(book_->endIter()))
      {
        foundBookmark->second = std::next(foundBookmark->second);
        ++counter;
      }
    } else if (steps < 0)
    {
      while (counter != steps && foundBookmark->second != book_->beginIter())
      {
        foundBookmark->second = std::prev(foundBookmark->second);
        --counter;
      }
    }
  } else
  {
    std::cout << INVALID_BOOKMARK;
  }
}

void PhoneBookContainer::moveBookmark(const std::string &bookmark, const MovePosition position)
{
  const auto foundBookmark = bookmarksMap_.find(bookmark);
  if (foundBookmark != bookmarksMap_.end())
  {
    if (position == MovePosition::FIRST)
    {
      foundBookmark->second = book_->beginIter();
    } else
    {
      foundBookmark->second = std::prev(book_->endIter());
    }
  } else
  {
    std::cout << INVALID_BOOKMARK;
  }
}
