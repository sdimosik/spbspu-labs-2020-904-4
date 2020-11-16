#ifndef FACTORIAL
#define FACTORIAL

#include <iterator>

class Factorial
{
public:
  Factorial() = default;

  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    Iterator();
    Iterator(const size_t argument);
    size_t& operator*();
    size_t* operator->();
    Iterator operator++();
    Iterator operator++(int);
    Iterator operator--();
    Iterator operator--(int);
    bool operator==(const Iterator& iterator);
    bool operator!=(const Iterator& iterator);

    const static size_t MIN_ARGUMENT = 1u;
    const static size_t MAX_ARGUMENT = 11u;
  private:
    size_t getFactorial(size_t argument) const;
    size_t argument_;
    size_t factorial_;
  };

  Iterator begin();
  Iterator end();
};

#endif // !FACTORIAL
