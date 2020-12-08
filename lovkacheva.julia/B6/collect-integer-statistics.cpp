#include "collect-integer-statistics.hpp"

const int TWO = 2;

lovkacheva::collectIntegerStatistics::collectIntegerStatistics():
  integerNumber_(0),
  positiveNumber_(0),
  negativeNumber_(0),
  max_(0),
  min_(0),
  evenSum_(0),
  oddSum_(0),
  first_(0),
  last_(0)
{}

void lovkacheva::collectIntegerStatistics::operator()(int integer)
{
  if (integerNumber_ == 0)
  {
    first_ = integer;
    min_ = integer;
    max_ = integer;
  }
  else
  {
    if (integer < min_)
    {
      min_ = integer;
    }
    else if (integer > max_)
    {
      max_ = integer;
    }
  }
  if (integer > 0)
  {
    ++positiveNumber_;
  }
  else if (integer < 0)
  {
    ++negativeNumber_;
  }
  if (integer % TWO == 0)
  {
    evenSum_ += integer;
  }
  else
  {
    oddSum_ += integer;
  }
  ++integerNumber_;
  last_  = integer;
}

int lovkacheva::collectIntegerStatistics::getMaxNumber() const
{
  return max_;
}

int lovkacheva::collectIntegerStatistics::getMinNumber() const
{
  return min_;
}

double lovkacheva::collectIntegerStatistics::getMean() const
{
  return static_cast<double>(evenSum_ + oddSum_) / integerNumber_;
}

size_t lovkacheva::collectIntegerStatistics::getNegativeNumber() const
{
  return negativeNumber_;
}

size_t lovkacheva::collectIntegerStatistics::getPositiveNumber() const
{
  return positiveNumber_;
}

long long lovkacheva::collectIntegerStatistics::getEvenSum() const
{
  return evenSum_;
}

long long lovkacheva::collectIntegerStatistics::getOddSum() const
{
  return oddSum_;
}

bool lovkacheva::collectIntegerStatistics::doFirstAndLastMatch() const
{
  return last_ == first_;
}

size_t lovkacheva::collectIntegerStatistics::getSize() const
{
  return integerNumber_;
}
