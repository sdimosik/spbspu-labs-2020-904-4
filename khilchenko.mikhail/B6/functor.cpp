#include "functor.hpp"

#include <limits>

Functor::Functor():
  max(std::numeric_limits<int>::min()),
  min(std::numeric_limits<int>::max()),
  firstNumber(0),
  amount(0),
  amountOfPositive(0),
  amountOfNegative(0),
  mean(0),
  sumOfOddElements(0),
  sumOfEvenElements(0)
{}

void Functor::operator()(int number)
{
  if(amount == 0)
  {
    firstNumber = number;
  }
  if(number > max)
  {
    max = number;
  }
  if(number < min)
  {
    min = number;
  }
  if(number > 0)
  {
    amountOfPositive++;
  }
  if(number < 0)
  {
    amountOfNegative++;
  }
  if(number % 2 == 0)
  {
    sumOfEvenElements += number;
  }
  else
  {
    sumOfOddElements += number;
  }

  amount++;
  lastNumber = number;
}

void Functor::print(std::ostream& out) const
{
  if(amount == 0)
  {
    out << "No Data\n";
    return;
  }

  out << "Max: " << max
      << "\nMin: " << min
      << "\nMean: " << (static_cast<double>(sumOfEvenElements + sumOfOddElements) / amount)
      << "\nPositive: " << amountOfPositive
      << "\nNegative: " << amountOfNegative
      << "\nOdd Sum: " << sumOfOddElements
      << "\nEven Sum: " << sumOfEvenElements
      << "\nFirst/Last Equal: " << (firstNumber == lastNumber ? "yes\n" : "no\n");
}
