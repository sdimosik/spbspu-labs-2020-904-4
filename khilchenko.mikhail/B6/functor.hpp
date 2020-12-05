#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <iostream>

class Functor
{
public:
  Functor();
  void operator()(int);
  void print(std::ostream&) const;
private:
  int max;
  int min;
  int firstNumber;
  int lastNumber;
  size_t amount;
  size_t amountOfPositive;
  size_t amountOfNegative;
  double mean;
  long sumOfOddElements;
  long sumOfEvenElements;
};

#endif
