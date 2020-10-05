#ifndef PRINT
#define PRINT
#include <iostream>

template <class container>
void print(const container& collection, const char* delimiter = "")
{
  for (auto i = collection.begin(); i != collection.end(); ++i)
  {
    std::cout << *i << delimiter;
  }
  std::cout << '\n';
}
#endif // !PRINT
