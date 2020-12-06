#include "functor.hpp"

#include <iostream>
#include <climits>

Functor::Functor():
  maxNumber_(INT_MIN),
  minNumber_(INT_MAX),
  quantityOfPositive_(0),
  quantityOfNegative_(0),
  oddSum_(0),
  evenSum_(0),
  isEqual(false),
  count_(0),
  firstNumber_(0)
{}

void Functor::operator()(int number)
{
  if (count_ == 0)
  {
    firstNumber_ = number;
  }

  if(number > maxNumber_)
  {
    maxNumber_ = number;
  }

  if(number < minNumber_)
  {
    minNumber_ = number;
  }

  if (number > 0)
  {
    quantityOfPositive_++;
  }

  if (number < 0)
  {
    quantityOfNegative_++;
  }

  number % 2 == 0 ? evenSum_ += number : oddSum_ += number;
  count_++;

  isEqual = (firstNumber_ == number);
}

void Functor::printInfo(std::ostream &out) const
{
  if(count_ == 0)
  {
    out << "No Data\n";
    return;
  }

  out << "Max: " << maxNumber_ << '\n' << "Min: " << minNumber_ << '\n'
      << "Mean: "  << std::fixed << static_cast<double>(oddSum_ + evenSum_) / (count_) << '\n'
      << "Positive: " << quantityOfPositive_ << '\n' << "Negative: " << quantityOfNegative_ << '\n'
      << "Odd Sum: " << oddSum_ << '\n' << "Even Sum: " << evenSum_ << '\n'
      << "First/Last Equal: " << ((isEqual) ? "yes" : "no") << '\n';
}
