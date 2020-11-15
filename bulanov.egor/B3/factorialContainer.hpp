#ifndef B3_FACTORIALCONTAINER_HPP
#define B3_FACTORIALCONTAINER_HPP
#include <iterator>

class FactorialContainer
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    static const size_t MIN_IND_ELEM = 1;

    static const size_t MAX_IND_ELEM = 11;

    Iterator();

    explicit Iterator(size_t);

    const size_t & operator*() const noexcept ;

    const size_t * operator->() const noexcept ;

    Iterator &operator++();

    Iterator operator++(int);

    Iterator &operator--();

    Iterator operator--(int);

    bool operator==(const Iterator & it) const;

    bool operator!=(const Iterator & it) const;

  private:
    size_t ind_elem_;
    size_t value_;
    size_t getFactorial(size_t index);
  };

  Iterator begin();

  Iterator end();
};



#endif
