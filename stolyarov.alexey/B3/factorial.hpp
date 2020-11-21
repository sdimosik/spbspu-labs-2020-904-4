#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include <iterator>

class Factorial
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    static const size_t MIN_INDEX = 1;

    static const size_t MAX_INDEX = 11;

    Iterator();

    Iterator(size_t index);

    const size_t& operator*() const noexcept;

    const size_t* operator->() const noexcept;

    Iterator& operator++();

    Iterator operator++(int);

    Iterator& operator--();

    Iterator operator--(int);

    bool operator==(const Iterator& it) const;

    bool operator!=(const Iterator& it) const;

  private:
    size_t value_;
    size_t index_;

    size_t getFactorial(size_t index) const;
  };

  Iterator begin();

  Iterator end();

};

#endif
