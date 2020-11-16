#include <stdexcept>
#include <vector>
#include <algorithm>
#include <iterator>

#include "dataStructure.hpp"

int main()
{
  try
  {
    std::vector<DataStructure> vector(std::istream_iterator<DataStructure>(std::cin),
        std::istream_iterator<DataStructure>());
    std::sort(vector.begin(), vector.end());
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStructure>(std::cout));
  }
  catch(std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error" << '\n';
    return 2;
  }
  return 0;
}
