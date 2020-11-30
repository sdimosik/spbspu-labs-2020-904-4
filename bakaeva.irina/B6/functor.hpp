#ifndef B6_FUNCTOR_HPP
#define B6_FUNCTOR_HPP

#include <iostream>

class Functor
{
public:
  Functor();

  void operator()(int number);

  void printInfo(std::ostream &out);

private:
  int maxNumber_;
  int minNumber_;
  double meanOfNumbers_;
  size_t countOfPositive_;
  size_t countOfNegative_;
  long long oddSum_;
  long long evenSum_;
  bool isFirstAndLastEqual_;

  int countOfZero_;
  int firstElement_;
};

#endif
