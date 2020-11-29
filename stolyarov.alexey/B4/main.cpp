#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <iterator>

#include "data-struct.hpp"

int main()
{
  try
  {
    std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());
    std::sort(vector.begin(), vector.end(), checkCondition);
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (const std::exception & e)
  {
    std::cout << e.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Reading data failure!\n";
    return 2;
  }

  return 0;
}
