#include "phone-book-interface.hpp"
#include <stdexcept>
#include <iostream>
#include <iterator>

PhoneBookInterface::PhoneBookInterface(std::unique_ptr<PhoneBook>&& phonebook)
{
  phonebook_ = std::move(phonebook);
  bookmarks_[CURRENT] = phonebook_->end();
}

void PhoneBookInterface::move(const std::string& steps, std::ostream& errorOut, const std::string& bookmark)
{
  if (bookmarks_.find(bookmark) == bookmarks_.end())
  {
    errorOut << "<INVALID BOOKMARK>" << '\n';
    return;
  }
  if (phonebook_->isEmpty())
  {
    errorOut << "<EMPTY>" << '\n';
    return;
  }
  if (steps == "first")
  {
    bookmarks_[bookmark] = phonebook_->begin();
    return;
  }
  if (steps == "last")
  {
    bookmarks_[bookmark] = std::prev(phonebook_->end());
    return;
  }
  int dist;
  try
  {
    dist = std::stoi(steps);
  }
  catch (std::exception&)
  {
    errorOut << "<INVALID STEP>" << '\n';
    return;
  }
  dist = (dist >= 0 ? (dist % phonebook_->size()) : -static_cast<int>(((abs(dist) % phonebook_->size()))));
  if (dist + static_cast<int>(std::distance(phonebook_->begin(), bookmarks_[bookmark])) < 0)
  {
    int temp = dist + static_cast<int>(std::distance(phonebook_->begin(), bookmarks_[bookmark]));
    dist = phonebook_->size() + temp;
    std::advance(bookmarks_[bookmark], dist);
  }
  else if (dist + static_cast<int>(std::distance(phonebook_->begin(), bookmarks_[bookmark]))
    >= static_cast<int>(phonebook_->size()))
  {
    int temp = dist + static_cast<int>(std::distance(phonebook_->begin(), bookmarks_[bookmark])) 
        - static_cast<int>(phonebook_->size());
    dist = temp + 1 - phonebook_->size();
    std::advance(bookmarks_[bookmark], dist);
  }
  else
  {
    std::advance(bookmarks_[bookmark], dist);
  }
}

void PhoneBookInterface::insertAfter(const std::string& number, const std::string& name, std::ostream& errorOut, 
    const std::string& bookmark)
{
  if (bookmark == CURRENT && bookmarks_[bookmark] == phonebook_->end())
  {
    phonebook_->insertToEnd(number, name);
    bookmarks_[bookmark] = phonebook_->begin();
    return;
  }
  PhoneBookInterface::IteratorType iter;
  try
  {
    iter = getBookmarkIter(bookmark);
  }
  catch (std::invalid_argument& error)
  {
    errorOut << error.what() << '\n';
    return;
  }
  phonebook_->insertAfter(number, name, iter);
}

void PhoneBookInterface::insertBefore(const std::string& number, const std::string& name, std::ostream& errorOut, 
    const std::string& bookmark)
{
  if (bookmark == CURRENT && bookmarks_[bookmark] == phonebook_->end())
  {
    phonebook_->insertToEnd(number, name);
    bookmarks_[bookmark] = phonebook_->begin();
    return;
  }
  PhoneBook::IteratorType iter;
  try
  {
    iter = getBookmarkIter(bookmark);
  }
  catch (std::invalid_argument& error)
  {
    errorOut << error.what() << '\n';
    return;
  }
  phonebook_->insertBefore(number, name, iter);
}

void PhoneBookInterface::insertToEnd(const std::string& number, const std::string& name)
{
  if (phonebook_->isEmpty())
  {
    phonebook_->insertToEnd(number, name);
    bookmarks_[CURRENT] = phonebook_->begin();
  }
  else
  {
    phonebook_->insertToEnd(number, name);
  }
}

void PhoneBookInterface::deleteBookmark(const std::string& bookmark, std::ostream& errorOut)
{
  PhoneBook::IteratorType current;
  try
  {
    current = getBookmarkIter(bookmark);
  }
  catch (std::invalid_argument& error)
  {
    errorOut << error.what() << '\n';
    return;
  }
  typename BookmarksType::iterator iter = bookmarks_.begin();
  while (iter != bookmarks_.end())
  {
    if (iter->second == current)
    {
      iter->second = std::next(current);
    }
    iter++;
  }
  phonebook_->deleteNote(std::prev(bookmarks_[bookmark]));
  iter = bookmarks_.begin();
  while (iter != bookmarks_.end())
  {
    if (iter->second == phonebook_->end())
    {
      if (!phonebook_->isEmpty())
      {
        iter->second = phonebook_->begin();
      }
    }
    iter++;
  }
}

void PhoneBookInterface::addBookmark(const std::string& oldMark, const std::string& newMark, std::ostream& errorOut)
{
  if (newMark == CURRENT || bookmarks_.find(oldMark) == bookmarks_.end())
  {
    errorOut << "<INVALID BOOKMARK>";
    return;
  }
  bookmarks_[newMark] = bookmarks_[oldMark];
}

void PhoneBookInterface::showBookmark(std::ostream& out, std::ostream& errorOut, const std::string& mark)
{
  try
  {
    phonebook_->showCurrent(out, getBookmarkIter(mark));
  }
  catch (std::invalid_argument& error)
  {
    errorOut << error.what() << '\n';
    return;
  }
}

PhoneBookInterface::IteratorType PhoneBookInterface::getBookmarkIter(const std::string& bookmark)
{
  if (bookmarks_.find(bookmark) == bookmarks_.end())
  {
    throw std::invalid_argument("<INVALID BOOKMARK>");
  }
  if (phonebook_->isEmpty())
  {
    throw std::invalid_argument("<EMPTY>");
  }
  return bookmarks_[bookmark];
}
