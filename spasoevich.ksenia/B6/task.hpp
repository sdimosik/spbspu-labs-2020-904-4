#ifndef TASK_B6_HPP
#define TASK_B6_HPP

struct StatsCollector
{
  int max;
  int min;
  double mean;
  int positive;
  int negative;
  long int evenSum;
  long int oddSum;
  bool firstEqLast;
  int size;
  StatsCollector();
  void operator ()(int num);

private:
  int first;
};

#endif

