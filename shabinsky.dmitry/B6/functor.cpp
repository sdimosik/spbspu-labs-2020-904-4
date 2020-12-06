#include "functor.hpp"
#include <limits>

Functor::Functor() :
  max_(std::numeric_limits<int>::min()),
  min_(std::numeric_limits<int>::max()),
  mean_(),
  amount_(),
  positive_(),
  negative_(),
  oddSum_(),
  evenSum_(),
  first_(),
  last_()
{}

void Functor::operator()(int number)
{
  if (number > max_)
  {
    max_ = number;
  }
  
  if (number < min_)
  {
    min_ = number;
  }
  
  if (mean_ == 0)
  {
    first_ = number;
  }
  ++mean_;
  
  if (number > 0)
  {
    ++positive_;
  }
  
  if (number < 0)
  {
    ++negative_;
  }
  
  number % 2 == 0 ? evenSum_ += number : oddSum_ += number;
  last_ = number;
  amount_++;
}

void Functor::print(std::ostream &out) const
{
  if (amount_ == 0)
  {
    out << "No Data\n";
    return;
  }
  
  out << "Max: " << max_
      << "\nMin: " << min_
      << "\nMean: " << (static_cast<double>(evenSum_ + oddSum_) / amount_)
      << "\nPositive: " << positive_
      << "\nNegative: " << negative_
      << "\nOdd Sum: " << oddSum_
      << "\nEven Sum: " << evenSum_
      << "\nFirst/Last Equal: " << (first_ == last_ ? "yes\n" : "no\n");
}
