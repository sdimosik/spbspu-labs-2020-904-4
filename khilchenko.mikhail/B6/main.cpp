#include <iterator>
#include <algorithm>

#include "functor.hpp"

int main()
{
  try
  {
    Functor functor = std::for_each(std::istream_iterator<int>(std::cin), std::istream_iterator<int>(), Functor());
    if(std::cin.fail() && !std::cin.eof())
    {
      throw std::runtime_error("Error in reading data");
    }
    functor.print(std::cout);
    return 0;
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
}
