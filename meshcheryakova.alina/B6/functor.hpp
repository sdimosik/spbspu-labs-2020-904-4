#ifndef B6_FUNCTOR_HPP
#define B6_FUNCTOR_HPP

#include <iostream>
#include <bits/stdc++.h>

class Functor
{
public:
  void operator()(int current);
  friend std::ostream& operator<<(std::ostream& out, const Functor& functor);

private:
  int full_count_ = 0;
  int max_ = INT_MIN;
  int min_ = INT_MAX;
  int positive_ = 0;
  int negative_ = 0;
  long int odd_sum_ = 0;
  long int even_sum_ = 0;
  int last_ = 0;
  int first_ = 0;
};

#endif //B6_FUNCTOR_HPP
