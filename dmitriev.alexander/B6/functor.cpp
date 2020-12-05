#include "functor.hpp"

Functor::Functor() :
  maxNumber_(std::numeric_limits<int>::min()),
  minNumber_(std::numeric_limits<int>::max()),
  numberCount_(0),
  positiveCount_(0),
  negativeCount_(0),
  oddSum_(0),
  evenSum_(0),
  firstNumber_(0),
  lastNumber_(0)
{}

void Functor::operator()(const int number)
{
  if (numberCount_ == 0)
  {
    firstNumber_ = number;
  }

  lastNumber_ = number;
  
  numberCount_++;

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
    positiveCount_++;
  } else if (number < 0)
  {
    negativeCount_++;
  }

  if (number % 2 == 0)
  {
    evenSum_ += number;
  } else
  {
    oddSum_ += number;
  }
}

std::ostream &operator<<(std::ostream &ostream, const Functor &functor)
{
  if (functor.numberCount_ == 0)
  {
    ostream << "No Data" << std::endl;
    return ostream;
  }

  const auto meanNumber = static_cast<double>(functor.oddSum_ + functor.evenSum_) / functor.numberCount_;

  std::string firstLastEqual = "no";
  if (functor.firstNumber_ == functor.lastNumber_)
  {
    firstLastEqual = "yes";
  }

  ostream << "Max: " << functor.maxNumber_ << std::endl
          << "Min: " << functor.minNumber_ << std::endl
          << "Mean: " << std::fixed << meanNumber << std::endl
          << "Positive: " << functor.positiveCount_ << std::endl
          << "Negative: " << functor.negativeCount_ << std::endl
          << "Odd Sum: " << functor.oddSum_ << std::endl
          << "Even Sum: " << functor.evenSum_ << std::endl
          << "First/Last Equal: " << firstLastEqual << std::endl;
  return ostream;
}
