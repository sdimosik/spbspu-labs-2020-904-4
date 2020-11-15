#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <iterator>
#include <functional>
#include "data-struct.hpp"

using namespace std::placeholders;

int main()
{
  std::vector<DataStruct> vector;
  try
  {
    DataStruct dataStruct;
    while (std::cin >> dataStruct)
    {
      vector.push_back(dataStruct);
    }
    if (!std::cin.eof() && std::cin.fail())
    {
      throw std::invalid_argument("Error while reading");
    }
    std::sort(vector.begin(), vector.end(), [](const DataStruct& dataStruct1, const DataStruct& dataStruct2)
      {
        return dataStruct1 < dataStruct2;
      });
    std::for_each(vector.begin(), vector.end(), std::bind(print, _1));
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  return 0;
}
