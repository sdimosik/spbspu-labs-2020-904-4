#include "task.hpp"
#include <iostream>
#include <algorithm>
#include <limits>
#include <stdexcept>
#include <iomanip>
#include <iterator>

Functor::Functor() :
  maxElement_(std::numeric_limits<int>::min()),
  minElement_(std::numeric_limits<int>::max()),
  mean_(0),
  positiveCount_(0),
  negativeCount_(0),
  sumOdd_(0),
  sumEven_(0),
  isEqualFirstToLast_(false),
  isEmpty_(true),
  countOfNumbers_(0),
  first_(0)
{}

void Functor::operator()(const int number)
{
  if (isEmpty_)
  {
    first_ = number;
    isEmpty_ = false;
  }
  countOfNumbers_++;
  if (number >= maxElement_)
  {
    maxElement_ = number;
  }
  if (number <= minElement_)
  {
    minElement_ = number;
  }
  if (number > 0)
  {
    positiveCount_++;
  }
  if (number < 0)
  {
    negativeCount_++;
  }
  if (number % 2 == 0)
  {
    sumEven_ += number;
  }
  else
  {
    sumOdd_ += number;
  }
  mean_ = static_cast<double>((sumEven_ + sumOdd_)) / countOfNumbers_;
  if (first_ == number)
  {
    isEqualFirstToLast_ = true;
  }
  else
  {
    isEqualFirstToLast_ = false;
  }
}

void task()
{
  Functor functor = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Functor());
  if (std::cin.fail() && !std::cin.eof())
  {
    throw std::runtime_error("Not a number entered");
  }
  if (functor.isEmpty_)
  {
    std::cout << "No Data\n";
    return;
  }
  std::cout << "Max: " << functor.maxElement_ << '\n';
  std::cout << "Min: " << functor.minElement_ << '\n';
  std::cout << "Mean: " << std::fixed << functor.mean_ << '\n';
  std::cout << "Positive: " << functor.positiveCount_ << '\n';
  std::cout << "Negative: " << functor.negativeCount_ << '\n';
  std::cout << "Odd Sum: " << functor.sumOdd_ << '\n';
  std::cout << "Even Sum: " << functor.sumEven_ << '\n';
  std::cout << "First/Last Equal: ";
  if (functor.isEqualFirstToLast_)
  {
    std::cout << "yes\n";
  }
  else
  {
    std::cout << "no\n";
  }
}
