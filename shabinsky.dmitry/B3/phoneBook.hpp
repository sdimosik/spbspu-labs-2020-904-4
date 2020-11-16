#ifndef B3_PHONEBOOK_HPP
#define B3_PHONEBOOK_HPP

#include <utility>
#include <string>
#include <list>
#include <stdexcept>
#include <map>

class PhoneBook
{
public:
  struct Note
  {
    std::string number_;
    std::string name_;
  };
  enum class MoveType
  {
    FIRST,
    LAST
  };
  
  using Iterator = std::list<Note>::iterator;
  
  Iterator insert(const PhoneBook::Note &note, Iterator it);
  
  Iterator replace(PhoneBook::Note &note, Iterator it);
  
  Iterator removeAt(Iterator it);
  
  Iterator beginIt();
  
  Iterator endIt();
  
  void pushBack(const Note &note);
  
  size_t size() const;

private:
  std::list<Note> notes_;
};

#endif //B3_PHONEBOOK_HPP
