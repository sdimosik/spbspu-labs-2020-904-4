#ifndef PRINT_CONTENTS_HPP
#define PRINT_CONTENTS_HPP
#include <iostream>
namespace lovkacheva
{
  template<class Container>
  void printContents(const Container& container, std::string delimiter = " ", bool newline = true,
      std::ostream& out = std::cout)
  {
    for (auto element : container)
    {
      out << element << delimiter;
    }
    if (newline)
    {
      out << '\n';
    }
  }
}
#endif
