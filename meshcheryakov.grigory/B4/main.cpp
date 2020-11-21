#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "dataStruct.hpp"

int main()
{
  try
  {
    std::vector<DataStruct> vec(std::istream_iterator<DataStruct>(std::cin), std::istream_iterator<DataStruct>());
    std::sort(vec.begin(), vec.end(), comparator);
    std::copy(vec.begin(), vec.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (const std::exception& e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error\n";
    return 2;
  }

  return 0;
}
