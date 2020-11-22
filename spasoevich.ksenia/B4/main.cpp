#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

#include "data-structure.hpp"

int main()
{
  try
  {
    std::vector<DataStructure> vector(std::istream_iterator<DataStructure>(std::cin),std::istream_iterator<DataStructure>());
    std::sort(vector.begin(), vector.end());
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStructure>(std::cout));
  }
  catch(std::exception& exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  return 0;
}


