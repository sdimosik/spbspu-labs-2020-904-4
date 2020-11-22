#ifndef B3_FACTORIAL_CONTAINER_HPP
#define B3_FACTORIAL_CONTAINER_HPP

#include <iterator>

class factorialContainer
{
  class Iterator: public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:

    Iterator();
    Iterator(size_t number);
    bool operator ==(const Iterator& rhs);
    bool operator !=(const  Iterator& rhs);
    Iterator operator ++();
    Iterator operator --();
    Iterator operator ++(int);
    Iterator operator --(int);
    const value_type& operator *() const;

  private:
    size_t number_;
    unsigned long value_;

    unsigned long get_value_from_number(size_t num) const;
  };

public:
  Iterator begin();
  Iterator end();

private:
  const static size_t max_size_ = 11;
};


#endif //B3_FACTORIAL_CONTAINER_HPP
