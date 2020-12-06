#ifndef B6_FUNCTOR_HPP
#define B6_FUNCTOR_HPP

#include <iostream>

class Functor
{
public:
  Functor();
  
  void operator()(int number);
  
  void print(std::ostream &out) const;

private:
  int max_;
  int min_;
  double mean_;
  size_t amount_;
  size_t positive_;
  size_t negative_;
  long long oddSum_;
  long long evenSum_;
  int first_;
  int last_;
};

#endif //B6_FUNCTOR_HPP
