#include "user-interface.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include "utilities.hpp"

const char* const INVALID_COMMAND = "<INVALID COMMAND>\n";

lovkacheva::UserInterface::UserInterface(const std::shared_ptr<PhoneBook>& phoneBook):
  phoneBook_(phoneBook)
{
  bookmarks_["current"] = phoneBook_->begin();
}

void lovkacheva::UserInterface::add(std::vector<std::string> args, std::ostream &out)
{
  if (args.size() == 2)
  {
    processName(args[1]);
    if (!isAPhoneNumber(args[0]) || args[1].empty())
    {
      out << INVALID_COMMAND;
    }
    else
    {
      phoneBook_->insertBack(args[1], args[0]);
      if (std::next(phoneBook_->begin()) == phoneBook_->end())
      {
        bookmarks_["current"] = phoneBook_->begin();
      }
    }
  }
  else
  {
    out << INVALID_COMMAND;
  }
}

void lovkacheva::UserInterface::store(std::vector<std::string> args, std::ostream &out)
{
  if (args.size() == 2)
  {
    if (!isABookmarkName(args[0]) || !isABookmarkName(args[1]))
    {
      out << INVALID_COMMAND;
    }
    else
    {
      BookmarksMap::iterator source = bookmarks_.find(args[0]);
      if (source == bookmarks_.end())
      {
        out << "<INVALID BOOKMARK>\n";
      }
      else
      {
        bookmarks_.insert({args[1], source->second});
      }
    }
  }
  else
  {
    out << INVALID_COMMAND;
  }
}

void lovkacheva::UserInterface::deleteEntry(std::vector<std::string> args, std::ostream &out)
{
  if (args.size() != 1 || !isABookmarkName(args[0]))
  {
    out << INVALID_COMMAND;
    return;
  }
  BookmarksMap::iterator bookmarkToDeleteIterator = bookmarks_.find(args[0]);
  if (bookmarkToDeleteIterator == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  lovkacheva::PhoneBook::iterator bookmarkToDelete = bookmarkToDeleteIterator->second;
  if (phoneBook_->size() == 1)
  {
    phoneBook_->erase(bookmarkToDelete);
    bookmarks_.clear();
    bookmarks_["current"] = phoneBook_->begin();
    return;
  }
  for (BookmarksMap::iterator i = bookmarks_.begin(); i != bookmarks_.end(); i++)
  {
    if (i->second == bookmarkToDelete)
    {
      lovkacheva::PhoneBook::iterator next = std::next(i->second);
      if (phoneBook_->end() == next)
      {
        i->second = std::prev(i->second);
      }
      else
      {
        i->second = next;
      }
    }
  }
  phoneBook_->erase(bookmarkToDelete);
}

void lovkacheva::UserInterface::show(std::vector<std::string> args, std::ostream &out)
{
  if (args.size() == 1)
  {
    BookmarksMap::iterator bookmark = bookmarks_.find(args[0]);
    if (bookmark == bookmarks_.end())
    {
      out << "<INVALID BOOKMARK>\n";
      return;
    }
    if (!phoneBook_->empty())
    {
      phoneBook_->show(bookmark->second, out);
    }
    else
    {
      out << "<EMPTY>\n";
    }
  }
  else
  {
    out << INVALID_COMMAND;
  }
}

void lovkacheva::UserInterface::insertEntry(std::vector<std::string> args, std::ostream &out)
{
  if (args.size() != 4)
  {
    out << INVALID_COMMAND;
    return;
  }
  processName(args[3]);
  if (!isABookmarkName(args[1]) || !isAPhoneNumber(args[2]) || args[3].empty())
  {
    out << INVALID_COMMAND;
    return;
  }
  BookmarksMap::iterator bookmark = bookmarks_.find(args[1]);
  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
  }
  else
  {
    if (args[0] == "before")
    {
      bookmark->second = phoneBook_->insertBefore(bookmark->second, args[3], args[2]);
    }
    else if (args[0] == "after")
    {
      bookmark->second = phoneBook_->insertAfter(bookmark->second, args[3], args[2]);
    }
    else
    {
      out << INVALID_COMMAND;
    }
  }
}

void lovkacheva::UserInterface::move(std::vector<std::string> args, std::ostream &out)
{
  if (args.size() != 2 || !isABookmarkName(args[0]))
  {
    out << INVALID_COMMAND;
    return;
  }
  BookmarksMap::iterator bookmark = bookmarks_.find(args[0]);
  if (bookmark == bookmarks_.end())
  {
    out << "<INVALID BOOKMARK>\n";
    return;
  }
  if (args[1] == "first")
  {
    bookmark->second = phoneBook_->begin();
  }
  else if (args[1] == "last")
  {
    bookmark->second = std::prev(phoneBook_->end());
  }
  else
  {
    std::istringstream in(args[1]);
    int steps = 0;
    in >> steps;
    if (in.fail() && !in.eof())
    {
      out << "<INVALID STEP>\n";
    }
    else
    {
      std::iterator_traits<lovkacheva::PhoneBook::iterator>::difference_type distance = 0;
      if (steps > 0)
      {
        distance = std::distance<lovkacheva::PhoneBook::iterator>(bookmark->second, phoneBook_->end());
      }
      else
      {
        distance = std::distance<lovkacheva::PhoneBook::iterator>(phoneBook_->begin(), bookmark->second);
      }
      if (abs(steps) <= distance)
      {
        std::advance(bookmark->second, steps);
      }
      else
      {
        throw std::invalid_argument("Can't move the bookmark outside the phone book");
      }
    }
  }
}
