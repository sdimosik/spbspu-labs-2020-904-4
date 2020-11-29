#ifndef LABS_FACTORIAL_HPP
#define LABS_FACTORIAL_HPP
#include <iterator>

class Container
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, unsigned int>
  {
  public:
    Iterator();
    explicit Iterator(unsigned int index);

    unsigned int operator->() const;
    unsigned int operator*() const;

    bool operator==(const Iterator& rhs) const;
    bool operator!=(const Iterator& rhs) const;

    Iterator& operator++();
    Iterator operator++(int);

    Iterator& operator--();
    Iterator operator--(int);
  private:
    unsigned int index_;
    unsigned int factorial_;
  };

  Container() = default;
  Iterator begin() const;
  Iterator end() const;
private:
  static const unsigned int BEGIN_VALUE = 1;
  static const unsigned int BEGIN_INDEX = 1;
  static const unsigned int END_INDEX = 11;
};
#endif
