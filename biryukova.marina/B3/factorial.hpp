#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP
#include <iterator>
#include <cstddef>

class Factorial
{
public:
  class IteratorFactorial: public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    static const size_t MIN_POSITION = 1;
    static const size_t MAX_POSITION = 11;
    IteratorFactorial();
    IteratorFactorial(size_t position);
    bool operator==(const IteratorFactorial& rhs) const noexcept;
    bool operator!=(const IteratorFactorial& rhs) const noexcept;
    const size_t* operator->() const noexcept;
    const size_t& operator*() const noexcept;
    IteratorFactorial& operator ++();
    IteratorFactorial& operator--();
    IteratorFactorial operator ++(int);
    IteratorFactorial operator--(int);
  private:
    size_t position_;
    size_t value_;
    size_t factorial(const size_t number);
  };
  Factorial() = default;
  IteratorFactorial begin();
  IteratorFactorial end();
};

#endif
