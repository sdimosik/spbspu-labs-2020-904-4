#include <iterator>
#include <algorithm>
#include <iostream>
#include "collect-integer-statistics.hpp"
int main(int argc, char *[])
{
  try
  {
    if (argc != 1)
    {
      throw std::invalid_argument("The program does not accept any arguments");
    }
    std::istream_iterator<int> inIt(std::cin);
    std::istream_iterator<int> end;
    lovkacheva::collectIntegerStatistics collectStatistics;
    collectStatistics = std::for_each(inIt, end, collectStatistics);
    if (std::cin.fail() && !std::cin.eof())
    {
      throw std::runtime_error("Invalid Input");
    }
    if (collectStatistics.getSize() != 0)
    {
      std::cout << "Max: " << collectStatistics.getMaxNumber() << '\n';
      std::cout << "Min: " << collectStatistics.getMinNumber() << '\n';
      std::cout << "Mean: " << collectStatistics.getMean() << '\n';
      std::cout << "Positive: " << collectStatistics.getPositiveNumber() << '\n';
      std::cout << "Negative: " << collectStatistics.getNegativeNumber() << '\n';
      std::cout << "Odd Sum: " << collectStatistics.getOddSum() << '\n';
      std::cout << "Even Sum: " << collectStatistics.getEvenSum() << '\n';
      std::cout << "First/Last Equal: " << (collectStatistics.doFirstAndLastMatch() ? "yes" : "no") << '\n';
    }
    else
    {
      std::cout << "No Data\n";
    }
    
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return 2;
  }
  return 0;
}
