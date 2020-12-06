#include <vector>
#include <iostream>
#include <algorithm>
#include <iterator>
#include "data-struct.hpp"
#include "utilities.hpp"
int main()
{
  try
  {
    std::vector<lovkacheva::DataStruct> dataVector;
    lovkacheva::readStructs(std::cin, dataVector);
    std::sort(dataVector.begin(), dataVector.end(), lovkacheva::less);
    std::ostream_iterator<lovkacheva::DataStruct> outIt(std::cout, "\n");
    std::copy(dataVector.begin(), dataVector.end(), outIt);
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
