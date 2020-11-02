#ifndef PHONE_BOOK_HPP
#define PHONE_BOOK_HPP
#include <string>
#include <list>

class PhoneBook
{
public:
  struct PhoneBookNote
  {
    std::string number;
    std::string name;
  };
  using ContainerType = std::list<PhoneBookNote>;
  using IteratorType = ContainerType::iterator;
  PhoneBook() = default;
  PhoneBook(const PhoneBook& rhs) = default;
  ~PhoneBook() = default;
  void insertAfter(const std::string& number, const std::string& name, IteratorType iter);
  void insertBefore(const std::string& number, const std::string& name, IteratorType iter);
  void replaceCurrent(const std::string& number, const std::string& name, IteratorType iter);
  void insertToEnd(const std::string& number, const std::string& name);
  void deleteNote(IteratorType iter);
  void showCurrent(std::ostream& out, IteratorType iter) const;
  IteratorType begin() noexcept;
  IteratorType end() noexcept;
  bool isEmpty() const noexcept;
  size_t size() const noexcept;
private:
  ContainerType phonebook_;
};

#endif
