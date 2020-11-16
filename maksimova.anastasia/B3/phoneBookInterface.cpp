#include "phoneBookInterface.hpp"

phoneBookInterface::phoneBookInterface(std::unique_ptr<phoneBook> &&phoneBook)
{
  phoneBook_ = std::move(phoneBook);
  marks_["current"] = phoneBook_->begin();
}

void phoneBookInterface::addNote(const phoneBook::phoneNote &note)
{
  phoneBook_->pushBack(note.number, note.name);
  if (phoneBook_->begin() == --phoneBook_->end())
  {
    marks_["current"] = phoneBook_->begin();
  }
}

void phoneBookInterface::eraseNote(const std::string &bookmark)
{
  auto it = marks_.find(bookmark);
  if(it == marks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  if(it->second == phoneBook_->end())
  {
    return;
  }
  auto eraseIt = it->second;
  for (auto &mark : marks_)
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
  phoneBook_->eraseNote(eraseIt);
}

void phoneBookInterface::insertAfter(const std::string &bookmark, const phoneBook::phoneNote &note)
{
  if (bookmark == "current" && marks_[bookmark] == phoneBook_->end())
  {
    addNote(note);
    return;
  }
  auto it = marks_.find(bookmark);
  if (it != marks_.end())
  {
    phoneBook_->insertAfter(note.number, note.name, it->second);
    if (marks_.size() == 1)
    {
      marks_["current"] = phoneBook_->begin();
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void phoneBookInterface::insertBefore(const std::string &bookmark, const phoneBook::phoneNote &note)
{
  if (bookmark == "current" && marks_[bookmark] == phoneBook_->end())
  {
    addNote(note);
    return;
  }
  auto it = marks_.find(bookmark);
  if (it != marks_.end())
  {
    phoneBook_->insertBefore(note.number, note.name, it->second);
    if (marks_.size() == 1)
    {
      marks_["current"] = phoneBook_->begin();
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void phoneBookInterface::storeBookmark(const std::string &bookmark, const std::string &newBookmark)
{
  auto it = marks_.find(bookmark);
  if (it != marks_.end())
  {
    marks_.insert(std::make_pair(newBookmark, it->second));
    return;
  }
  std::cout << "<INVALID BOOKMARK>\n";
}

void phoneBookInterface::showNote(std::ostream &out, const std::string &bookmark)
{
  auto it = marks_.find(bookmark);
  if (it == marks_.end())
  {
    std::cout << "<INVALID BOOKMARK>\n";
    return;
  }
  if (it->second == phoneBook_->end())
  {
    std::cout << "<EMPTY>\n";
    return;
  }
  phoneBook_->showCurrent(out, it->second);
}

void phoneBookInterface::moveBookmark(const std::string &bookmark, const position &position)
{
  auto it = marks_.find(bookmark);
  if (it != marks_.end())
  {
    if(position == position::FIRST)
    {
      it->second = phoneBook_->begin();
    }
    else if(position == position::LAST)
    {
      it->second = std::prev(phoneBook_->end());
    }
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}

void phoneBookInterface::moveBookmark(const std::string &bookmark, const int steps)
{
  auto it = marks_.find(bookmark);
  if (it != marks_.end())
  {
    it->second = phoneBook_->move(it->second, steps);
  }
  else
  {
    std::cout << "<INVALID BOOKMARK>\n";
  }
}
