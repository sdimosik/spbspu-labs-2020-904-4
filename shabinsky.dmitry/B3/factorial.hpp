//
// Created by sdimosik on 29.10.2020.
//

#ifndef B3_FACTORIAL_HPP
#define B3_FACTORIAL_HPP

#include <iterator>

class Factorial
{
public:
  class Iterator : public std::iterator<std::bidirectional_iterator_tag, size_t>
  {
  public:
    static const size_t MIN_POS = 1;
    
    static const size_t MAX_POS = 11;
    
    static size_t getFactorial(size_t);
    
    Iterator();
    
    Iterator(size_t);
    
    size_t &operator*();
    
    size_t *operator->();
    
    Iterator &operator++();
    
    const Iterator operator++(int);
    
    Iterator &operator--();
    
    const Iterator operator--(int);
    
    bool operator==(const Iterator &) const;
    
    bool operator!=(const Iterator &) const;
  
  private:
    size_t position_;
    size_t value_;
  };
  
  Factorial() = delete;
  
  static Iterator begin();
  
  static Iterator end();
};

#endif //B3_FACTORIAL_HPP
