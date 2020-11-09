#ifndef FACTORIAL_HPP
#define FACTORIAL_HPP
#include <iterator>
namespace lovkacheva
{
  class Factorial
  {
  public:
    class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
    {
    public:
      Iterator();
      Iterator(size_t value, size_t index);
      size_t &operator*();
      size_t *operator->();
      Iterator operator++(int);
      Iterator operator++();
      Iterator operator--(int);
      Iterator operator--();
      bool operator==(const Iterator &rhs);
      bool operator!=(const Iterator &rhs);

    private:
      size_t index_;
      size_t value_;
    };
    Iterator begin();
    Iterator end();
  };
}
#endif
