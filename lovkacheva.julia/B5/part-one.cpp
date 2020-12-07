#include "parts.hpp"
#include <unordered_set> 
#include <string>
#include <iostream>
#include <iterator>
#include <algorithm>

void lovkacheva::partOne()
{
  std::unordered_set<std::string> words;
  std::insert_iterator<std::unordered_set<std::string>> target = std::inserter(words, words.begin());
  std::istream_iterator<std::string> inIt(std::cin);
  std::istream_iterator<std::string> end;
  std::copy(inIt, end, target);
  std::ostream_iterator<std::string> outIt(std::cout, "\n");
  std::copy(words.begin(), words.end(), outIt);
}
