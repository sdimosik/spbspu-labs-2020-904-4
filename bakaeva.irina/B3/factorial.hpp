#ifndef B3_FACTORIAL_HPP
#define B3_FACTORIAL_HPP
#include <iterator>

class Factorial
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    static const size_t MIN_ORDER = 1;

    static const size_t MAX_ORDER = 11;

    Iterator();

    Iterator(size_t);

    const size_t &operator*() const noexcept;

    const size_t *operator->() const noexcept;

    Iterator &operator++();

    Iterator operator++(int);

    Iterator &operator--();

    Iterator operator--(int);

    bool operator==(const Iterator &rhs) const;

    bool operator!=(const Iterator &rhs) const;

  private:
    size_t order_;
    size_t value_;

    size_t getFactorial(size_t index) const;
  };

  Factorial() = default;

  Iterator begin();

  Iterator end();
};

#endif
