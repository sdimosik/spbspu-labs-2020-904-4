#ifndef B6_FUNCTOR_HPP
#define B6_FUNCTOR_HPP

#include <iostream>


class Functor
{
public:
  Functor();

  void operator()(int number);

  void printInfo(std::ostream &out) const;

private:
  int maxNumber_;
  int minNumber_;
  int quantityOfPositive_;
  int quantityOfNegative_;
  long long oddSum_;
  long long evenSum_;
  bool isEqual;
  int count_;
  int firstNumber_;
};


#endif
