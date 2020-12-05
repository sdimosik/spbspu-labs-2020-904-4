#ifndef FUNCTOR_HPP
#define FUNCTOR_HPP

#include <limits>
#include <iostream>

class Functor
{
public:
  Functor();

  void operator()(int);

  friend std::ostream &operator<<(std::ostream &, const Functor &);

private:
  int maxNumber_;

  int minNumber_;

  unsigned int numberCount_;

  unsigned int positiveCount_;

  unsigned int negativeCount_;

  long long oddSum_;

  long long evenSum_;

  int firstNumber_;

  int lastNumber_;

};

#endif
