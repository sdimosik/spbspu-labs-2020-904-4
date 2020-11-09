#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP

#include <iterator>
#include <list>
#include <string>

class phoneBook
{
public:

  struct record_t
  {
    std::string name;
    std::string number;
  };

  using Conatiner = std::list<record_t>;
  using Iterator=Conatiner::iterator;

  void showCurrentRecord(std::ostream& out, Iterator iter) const;
  void insertAfter(const std::string& number, const std::string& name, Iterator iter);
  void insertBefore(const std::string& number, const std::string& name, Iterator iter);
  void insertAtEnd(const std::string& number, const std::string& name);
  void replaceCurrentRecord(const std::string& number, const std::string& name, Iterator iter);
  void remove(Iterator iter);
  Iterator begin() noexcept;
  Iterator end() noexcept;
  bool isEmpty() const noexcept;
  size_t getSize() const noexcept;
private:
  Conatiner list;
};

#endif

