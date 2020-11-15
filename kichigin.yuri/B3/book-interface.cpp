#include "book-interface.hpp"
#include <iostream>

BookInterface::BookInterface(TelephoneBook& book) :
  book_(std::make_unique<TelephoneBook>(book))
{
  bookmarks_.insert(std::make_pair("current", book_->begin()));
}

void BookInterface::add(Note& note)
{
  book_->insertBack(note);
  if (bookmarks_.size() == 1)
  {
    bookmarks_["current"] = book_->begin();
  }
}

void BookInterface::store(std::string& bookmark, std::string& newBookmark, std::ostream& out)
{
  auto iterator = bookmarks_.find(bookmark);
  if (iterator != bookmarks_.end())
  {
    bookmarks_.insert(std::make_pair(newBookmark, iterator->second));
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void BookInterface::insertBefore(std::string& bookmark, Note& note, std::ostream& out)
{
  if (bookmark == "current" && book_->isEmpty())
  {
    add(note);
    return;
  }

  auto iterator = bookmarks_.find(bookmark);
  if (iterator != bookmarks_.end())
  {
    book_->insertBefore(note, iterator->second);
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void BookInterface::insertAfter(std::string& bookmark, Note& note, std::ostream& out)
{
  if (bookmark == "current" && book_->isEmpty())
  {
    add(note);
    return;
  }

  auto iterator = bookmarks_.find(bookmark);
  if (iterator != bookmarks_.end())
  {
    book_->insertAfter(note, iterator->second);
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void BookInterface::deleteNote(std::string& bookmark, std::ostream& out)
{
  auto iterator = bookmarks_.find(bookmark);
  if (iterator != bookmarks_.end())
  {
    auto noteForDelete = iterator->second;
    for (auto& eachBookmark : bookmarks_)
    {
      if (eachBookmark.second == noteForDelete)
      {
        if (std::next(eachBookmark.second) != book_->end())
        {
          eachBookmark.second = std::next(noteForDelete);
        }
        else
        {
          eachBookmark.second = book_->begin();
        }
      }
    }

    book_->deleteNote(noteForDelete);
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void BookInterface::show(std::string& bookmark, std::ostream& out) const
{
  auto iterator = bookmarks_.find(bookmark);
  if (iterator != bookmarks_.end())
  {
    if (book_->isEmpty())
    {
      out << "<EMPTY>\n";
      return;
    }
    if (iterator->second != book_->end())
    {
      out << iterator->second->second << ' ' << iterator->second->first << '\n';
    }
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void BookInterface::move(std::string& bookmark, int steps, std::ostream& out)
{
  auto iterator = bookmarks_.find(bookmark);
  if (iterator != bookmarks_.end())
  {
    if (steps > 0)
    {
      while (steps != 0 && iterator->second != book_->end())
      {
        iterator->second = std::next(iterator->second);
        --steps;
      }
    }
    else
    {
      while (steps != 0 && iterator->second != book_->begin())
      {
        iterator->second = std::prev(iterator->second);
        ++steps;
      }
    }
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}

void BookInterface::move(std::string& bookmark, KeyWord keyWord, std::ostream& out)
{
  auto iterator = bookmarks_.find(bookmark);
  if (iterator != bookmarks_.end())
  {
    switch (keyWord)
    {
    case KeyWord::FIRST:
      iterator->second = book_->begin();
      break;
    case KeyWord::LAST:
      iterator->second = (book_->isEmpty() ? book_->end() : std::prev(book_->end()));
      break;
    default:
      break;
    }
  }
  else
  {
    out << "<INVALID BOOKMARK>\n";
  }
}
