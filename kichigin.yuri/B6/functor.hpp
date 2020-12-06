#ifndef FUNCTOR
#define FUNCTOR
#include <iosfwd>

class Functor
{
public:
  Functor();
  void operator()(const int number);
  void print(std::ostream& out) const;
  void clear();
private:
  int maxNumber_;
  int minNumber_;
  size_t positiveCount_;
  size_t negativeCount_;
  long long oddSum_;
  long long evenSum_;
  int firstNumber_;
  int lastNumber_;
  size_t count_;
};

#endif // !FUNCTOR
