#ifndef LAB3_FACTORIAL_HPP
#define LAB3_FACTORIAL_HPP

#include <iterator>
#include <cstddef>

class Factorial
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, int>
  {
  public:

    Iterator();

    explicit Iterator(size_t index);

    size_t & operator*();

    size_t * operator->();

    Iterator operator++();

    Iterator operator++(int);

    Iterator operator--();

    Iterator operator--(int);

    bool operator==(Iterator & it) const;

    bool operator!=(Iterator & it) const;

  private:
    static size_t getValue(size_t index);
    size_t value_;
    size_t index_;
  };

  Iterator begin();

  Iterator end();
};

#endif
