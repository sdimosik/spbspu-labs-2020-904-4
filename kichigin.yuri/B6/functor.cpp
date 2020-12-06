#include "functor.hpp"
#include <climits>
#include <iostream>

Functor::Functor():
  maxNumber_(INT_MIN),
  minNumber_(INT_MAX),
  positiveCount_(0),
  negativeCount_(0),
  oddSum_(0),
  evenSum_(0),
  firstNumber_(0),
  lastNumber_(0),
  count_(0)
{}

void Functor::operator()(const int number)
{
  if (count_ == 0)
  {
    firstNumber_ = number;
  }

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
    ++positiveCount_;
  }
  else if (number < 0)
  {
    ++negativeCount_;
  }

  if (number % 2 == 0)
  {
    evenSum_ += number;
  }
  else
  {
    oddSum_ += number;
  }

  lastNumber_ = number;
  ++count_;
}

void Functor::print(std::ostream& out) const
{
  if (count_ == 0)
  {
    out << "No Data\n";
  }
  else
  {
    out << "Max: " << maxNumber_
        << "\nMin: " << minNumber_
        << "\nMean: " << (static_cast<double>(oddSum_ + evenSum_) / count_)
        << "\nPositive: " << positiveCount_
        << "\nNegative: " << negativeCount_
        << "\nOdd Sum: " << oddSum_
        << "\nEven Sum: " << evenSum_
        << "\nFirst/Last Equal: " << ((firstNumber_ == lastNumber_) ? "yes\n" : "no\n");
  }
}

void Functor::clear()
{
  maxNumber_ = INT_MIN;
  minNumber_ = INT_MAX;
  positiveCount_ = 0;
  negativeCount_ = 0;
  oddSum_ = 0;
  evenSum_ = 0;
  firstNumber_ = 0;
  lastNumber_ = 0;
  count_ = 0;
}
