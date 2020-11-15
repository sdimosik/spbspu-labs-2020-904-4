#ifndef SPBSPU_LABS_2020_904_4_PHONEBOOK_HPP
#define SPBSPU_LABS_2020_904_4_PHONEBOOK_HPP

#include <iostream>
#include <list>

class PhoneBook
{
public:
  struct Records
  {
    std::string number_;
    std::string name_;
  };

  using container = std::list<Records>;
  using iterator = container::iterator;

  void showThisRecord(iterator iter) const;

  void pushBack(const Records &record);

  iterator insertBefore(iterator iter, const Records &record);

  iterator insertAfter(iterator iter, const Records &record);

  iterator erase(iterator iter);

  iterator begin() noexcept;

  iterator end() noexcept;

private:
  container book_;
};


#endif
