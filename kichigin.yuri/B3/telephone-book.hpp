#ifndef TELEPHONE_BOOK
#define TELEPHONE_BOOK
#include <list>
#include <string>

class TelephoneBook
{
public:
  using Note = std::pair<std::string, std::string>;
  using Iterator = std::list<Note>::iterator;

  Iterator insertBefore(Note& note, Iterator iterator);
  Iterator insertAfter(Note& note, Iterator iterator);
  Iterator replace(Note& note, Iterator iterator);
  void insertBack(Note& note);
  Iterator deleteNote(Iterator iterator);
  bool isEmpty() const noexcept;
  Iterator begin();
  Iterator end();
  
private:
  std::list<Note> container_;
};


#endif // !TELEPHONE_BOOK
