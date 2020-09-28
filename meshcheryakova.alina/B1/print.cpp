#include <iostream>
#include <cstring>
#include <iterator>

template<typename T>
void print(const T& collection, const char* space = " ")
{
  std::copy(collection.begin(), collection.end(),
            std::ostream_iterator<typename T::value_type>(std::cout, space));
  if(std::strcmp(space, " ") == 0)
  {
    std::cout << '\n';
  }
}
