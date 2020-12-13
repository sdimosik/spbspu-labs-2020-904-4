#ifndef COLLECT_INTEGER_STATISTICS
#define COLLECT_INTEGER_STATISTICS
#include <utility>
#include <cstddef>
namespace lovkacheva
{
  class collectIntegerStatistics
  {
  public:
    collectIntegerStatistics();
    void operator()(int integer);
    int getMaxNumber() const;
    int getMinNumber() const;
    double getMean() const;
    size_t getNegativeNumber() const;
    size_t getPositiveNumber() const;
    long long getEvenSum() const;
    long long getOddSum() const;
    bool doFirstAndLastMatch() const;
    size_t getSize() const;
  private:
    size_t integerNumber_;
    size_t positiveNumber_;
    size_t negativeNumber_;
    int max_;
    int min_;
    long long evenSum_;
    long long oddSum_;
    int first_;
    int last_;
  };
}
#endif
