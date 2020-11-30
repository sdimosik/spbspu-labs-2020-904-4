#ifndef TASK_HPP
#define TASK_HPP
#include <cstddef>

void task();

struct Functor
{
public:
  int maxElement_;
  int minElement_;
  double mean_;
  size_t positiveCount_;
  size_t negativeCount_;
  long long sumOdd_;
  long long sumEven_;
  bool isEqualFirstToLast_;
  bool isEmpty_;
  Functor();
  void operator()(const int number);
private:
  size_t countOfNumbers_;
  int first_;
};

#endif
