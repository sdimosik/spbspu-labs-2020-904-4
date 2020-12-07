#include "functor.hpp"
#include <iostream>

void Functor::operator()(int const current)
{
  if(full_count_ == 0)
  {
    first_ = current;
  }
  full_count_++;

  if(current > max_)
  {
    max_ = current;
  }

  if(current < min_)
  {
    min_ = current;
  }

  if(current > 0 )
  {
    positive_++;
  }

  if(current < 0)
  {
    negative_++;
  }

  if(current % 2 == 0)
  {
    even_sum_ += current;
  }
  else
  {
    odd_sum_ += current;
  }
  last_ = current;
}

std::ostream &operator<<(std::ostream &out, const Functor &functor)
{
  if (functor.full_count_ == 0)
  {
    out << "No Data" << '\n';
    return out;
  }

  const auto mean = static_cast<double>(functor.odd_sum_ + functor.even_sum_) / functor.full_count_;
  std::string first_equal_to_last = "no";
  if (functor.first_ == functor.last_)
  {
    first_equal_to_last = "yes";
  }

  out << "Max: " << functor.max_ << '\n'
      << "Min: " << functor.min_ << '\n'
      << "Mean: " << std::fixed << mean << '\n'
      << "Positive: " << functor.positive_ << '\n'
      << "Negative: " << functor.negative_ << '\n'
      << "Odd Sum: " << functor.odd_sum_ << '\n'
      << "Even Sum: " << functor.even_sum_ << '\n'
      << "First/Last Equal: " << first_equal_to_last << '\n';
  return out;
}

