#include <stdexcept>
#include <string>
#include <memory>
#include <functional>

namespace lovkacheva::detail
{
  template <class T>
  std::function<bool(T, T)> getCompare(std::string order)
  {
    if (order == "ascending")
    {
      return std::greater<T>();
    }
    else if (order == "descending")
    {
      return std::less<T>();
    }
    else
    {
      throw std::invalid_argument("Invalid sorting order (order = " + order + ")");
    }
  }
}
