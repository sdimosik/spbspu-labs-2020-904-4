#include <iostream>
#include <algorithm>
#include "phonebook-interface.hpp"


phoneBookInterface::phoneBookInterface(std::unique_ptr<phoneBook>&& phonebook)
{
  PhoneBook = std::move(phonebook);  
  bookmarks["current"] = PhoneBook->end();
}

void phoneBookInterface::add(const std::string& oldMark, const std::string& newMark, std::ostream& Error)
{
  
  if (newMark == "current" || bookmarks.find(oldMark) == bookmarks.end())
  {
    Error<< "<INVALID BOOKMARK>";
    return;

  }
  bookmarks[newMark] = bookmarks[oldMark];
};

void phoneBookInterface::insertAfter(const std::string& number, const std::string& name, std::ostream& Error, const std::string& bookmark)
{
  if (bookmark == "current" && bookmarks[bookmark] == PhoneBook->end())
  {
    PhoneBook->insertAtEnd(number, name);
    bookmarks[bookmark] = PhoneBook->begin();
    return;
  }
  phoneBookInterface::Iterator iter;
  try
  {
    iter = getBookmarkIter(bookmark);
  }
  catch (std::invalid_argument& error)
  {
    Error << error.what() << '\n';
    return;
  }
  PhoneBook->insertAfter(number, name, iter);
};

void phoneBookInterface::insertBefore(const std::string& number, const std::string& name, std::ostream& Error, const std::string& bookmark)
{
  if (bookmark == "current" && bookmarks[bookmark] == PhoneBook->end())
  {
    PhoneBook->insertAtEnd(number, name);
    bookmarks[bookmark] = PhoneBook->begin();
    return;
  }
  phoneBook::Iterator iter;
  try
  {
    iter = getBookmarkIter(bookmark);
  }
  catch (std::invalid_argument& error)
  {
    Error << error.what() << '\n';
    return;
  }
  PhoneBook->insertBefore(number, name, iter);
}

void phoneBookInterface::insertAtEnd(const std::string& number, const std::string& name)
{
  if (PhoneBook->isEmpty())
  {
    PhoneBook->insertAtEnd(number, name);
    bookmarks["current"] = PhoneBook->begin();
  }
  else
  {
    PhoneBook->insertAtEnd(number, name);
  }
};

void phoneBookInterface::deleteNote(const std::string& bookmark, std::ostream& Error)
{
  phoneBook::Iterator current;
  try
  {
    current = getBookmarkIter(bookmark);
  }
  catch (std::invalid_argument& error)
  {
    Error << error.what() << '\n';
    return;
  }
  typename BookmarksType::iterator iter = bookmarks.begin();
  while (iter != bookmarks.end())
  {
    if (iter->second == current)
    {
      iter->second = std::next(current);
    }
    iter++;
  }
  PhoneBook->remove(std::prev(bookmarks[bookmark]));
  iter = bookmarks.begin();
  while (iter != bookmarks.end())
  {
    if (iter->second == PhoneBook->end())
    {
      if (!PhoneBook->isEmpty())
      {
        iter->second = PhoneBook->begin();
      }
    }
    iter++;
  }
};

void phoneBookInterface::show(std::ostream& out, std::ostream& Error, const std::string& mark)
{
  try
  {
    PhoneBook->showCurrentRecord(out, getBookmarkIter(mark));
  }
  catch (std::invalid_argument& error)
  {
    Error << error.what() << '\n';
    return;
  }
};

void phoneBookInterface::move(const std::string& steps, std::ostream& Error, const std::string& bookmark)
{
  if (bookmarks.find(bookmark) == bookmarks.end())
  {
      Error << "<INVALID BOOKMARK>"<< '\n';
      return;
  }
  if (PhoneBook->isEmpty())
  {
    Error << "<EMPTY>"<< '\n';
    return;
  }
  if (steps == "first")
  {
    bookmarks[bookmark] = PhoneBook->begin();
    return;
  }
  if (steps == "last")
  {
    bookmarks[bookmark] = std::prev(PhoneBook->end());
    return;
  }
  int dist;
  try
  {
    dist = std::stoi(steps);
  }
  catch (std::exception&)
  {
    Error << "<INVALID STEP>"<< '\n';
    return;
  }
  dist = (dist >= 0 ? (dist % PhoneBook->getSize()) : -static_cast<int>(((abs(dist) % PhoneBook->getSize()))));
  if (dist + static_cast<int>(std::distance(PhoneBook->begin(), bookmarks[bookmark])) < 0)
  {
    int temp = dist + static_cast<int>(std::distance(PhoneBook->begin(), bookmarks[bookmark]));
    dist = PhoneBook->getSize() + temp;
    std::advance(bookmarks[bookmark], dist);
  }
  else if (dist + static_cast<int>(std::distance(PhoneBook->begin(), bookmarks[bookmark]))>= static_cast<int>(PhoneBook->getSize()))
  {
    int temp = dist + static_cast<int>(std::distance(PhoneBook->begin(), bookmarks[bookmark]))- static_cast<int>(PhoneBook->getSize());
    dist = temp + 1 - PhoneBook->getSize();
    std::advance(bookmarks[bookmark], dist);
  }
  else
  {
    std::advance(bookmarks[bookmark], dist);
  }
};

phoneBookInterface::Iterator phoneBookInterface::getBookmarkIter(const std::string& bookmark)
{
  if (bookmarks.find(bookmark) == bookmarks.end())
  {
      throw std::invalid_argument("<INVALID BOOKMARK>");
  }
  if (PhoneBook->isEmpty())
  {
      throw std::invalid_argument("<EMPTY>");
  }
    return bookmarks[bookmark];
 };
