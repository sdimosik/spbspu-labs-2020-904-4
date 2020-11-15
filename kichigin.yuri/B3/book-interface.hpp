#ifndef BOOK_INTERFACE
#define BOOK_INTERFACE
#include <map>
#include <iosfwd>
#include <memory>
#include "telephone-book.hpp"

class BookInterface
{
public:
  enum class KeyWord
  {
    FIRST,
    LAST
  };
  using Note = TelephoneBook::Note;
  BookInterface(TelephoneBook& book);
  void add(Note& note);
  void store(std::string& bookmark, std::string& newBookmark, std::ostream& out);
  void insertBefore(std::string& bookmark, Note& note, std::ostream& out);
  void insertAfter(std::string& bookmark, Note& note, std::ostream& out);
  void deleteNote(std::string& bookmark, std::ostream& out);
  void show(std::string& bookmark, std::ostream& out) const;
  void move(std::string& bookmark, int steps, std::ostream& out);
  void move(std::string& bookmark, KeyWord keyWord, std::ostream& out);
private:
  std::unique_ptr<TelephoneBook> book_;
  std::map<std::string, TelephoneBook::Iterator> bookmarks_;
};

#endif // !BOOK_INTERFACE
