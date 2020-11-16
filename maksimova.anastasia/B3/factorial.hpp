#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP

#include <iterator>


class Factorial
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    static const size_t MIN_POS = 1;
    static const size_t MAX_POS = 11;
    Iterator();
    Iterator(size_t pos);
    const size_t* operator->() const noexcept;
    const size_t& operator*() const noexcept;
    bool operator==(const Iterator& rhs) const noexcept;
    bool operator!=(const Iterator& rhs) const noexcept;
    Iterator &operator++();
    Iterator operator++(int);
    Iterator &operator--();
    Iterator operator--(int);
  private:
    size_t factorial(const size_t number);
    size_t pos_;
    size_t value_;
  };
  Factorial() = default;
  Iterator begin();
  Iterator end();
};


#endif
