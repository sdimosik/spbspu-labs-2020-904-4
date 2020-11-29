#include <iostream>
#include <vector>
#include <iterator>
#include "data_struct.hpp"

int main(){
  try
  {
    DataStruct data;
    std::vector<DataStruct> vector((std::istream_iterator<DataStruct>(std::cin)), std::istream_iterator<DataStruct>());
    if ((!std::cin.eof()) && (std::cin.fail()))
    {
      throw std::ios_base::failure( " fail in reading stream! \n");
    }
    std::sort(vector.begin(), vector.end(), std::less<DataStruct>());
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(std::cout, "\n"));
  }
  catch (std::exception& exception)
  {
    std::cerr << exception.what() << "\n";
    return 1;
  }
  return 0;
}
