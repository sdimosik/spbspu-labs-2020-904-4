#include "functor.hpp"
#include <iostream>
#include <climits>

Functor::Functor() :
  maxNumber_(INT_MIN),
  minNumber_(INT_MAX),
  meanOfNumbers_(0),
  countOfPositive_(0),
  countOfNegative_(0),
  oddSum_(0),
  evenSum_(0),
  isFirstAndLastEqual_(false),
  countOfZero_(0),
  firstElement_(0)
{}

void Functor::operator()(int number)
{
  if (number > maxNumber_)
  {
    maxNumber_ = number;
  }

  if (number < minNumber_)
  {
    minNumber_ = number;
  }

  if (number > 0)
  {
    countOfPositive_++;
  }

  if (number < 0)
  {
    countOfNegative_++;
  }

  if (number == 0)
  {
    countOfZero_++;
  }

  (number % 2 == 0) ? evenSum_ += number : oddSum_ += number;

  meanOfNumbers_ = static_cast<double>(oddSum_ + evenSum_) / (countOfPositive_ + countOfNegative_ + countOfZero_);

  if ((countOfZero_ + countOfNegative_ + countOfPositive_) == 1)
  {
    firstElement_ = number;
  }

  isFirstAndLastEqual_ = (firstElement_ == number);
}

void Functor::printInfo(std::ostream &out)
{
  if ((countOfPositive_ + countOfNegative_ + countOfZero_) == 0)
  {
    out << "No Data" << '\n';
    return;
  }
  out << "Max: " << maxNumber_ << '\n'
      << "Min: " << minNumber_ << '\n'
      << "Mean: "  << std::fixed << meanOfNumbers_ << '\n'
      << "Positive: " << countOfPositive_ << '\n'
      << "Negative: " << countOfNegative_ << '\n'
      << "Odd Sum: " << oddSum_ << '\n'
      << "Even Sum: " << evenSum_ << '\n'
      << "First/Last Equal: " << ((isFirstAndLastEqual_) ? "yes" : "no") << '\n';
}
