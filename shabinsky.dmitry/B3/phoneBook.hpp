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
  enum class InsertType
  {
    BEFORE,
    AFTER
  };
  enum class MoveType
  {
    FIRST,
    LAST
  };
  
  using Iterator = std::list<Note>::iterator;
  
  void show(Iterator it);
  
  Iterator next(Iterator it);
  
  Iterator prev(Iterator it);
  
  Iterator insert(const PhoneBook::Note &note, PhoneBook::InsertType type, Iterator it);
  
  Iterator replace(PhoneBook::Note &note, Iterator it);
  
  Iterator move(int step, Iterator it);
  
  Iterator remove(Iterator it);
  
  Iterator begin();
  
  Iterator end();
  
  void push_back(const Note &note);
  
  size_t size() const;

private:
  std::list<Note> notes_;
};

#endif //B3_PHONEBOOK_HPP
