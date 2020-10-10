#include <vector>

#include "output.hpp"

void task3()
{
  std::vector<int> vector;
  int num = 0;

  while (std::cin >> num)
  {
    if (num == 0)
    {
      break;
    }
    vector.push_back(num);
  }

  if (!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Fail while reading data.");
  }

  if (vector.empty())
  {
    return;
  }

  if (num != 0)
  {
    throw std::runtime_error("No zero.");
  }



  if (vector.back() == 1)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      i = ((*i % 2) == 0) ? vector.erase(i) : ++i;
    }
  }
  if (vector.back() == 2)
  {
    for (auto i = vector.begin(); i != vector.end();)
    {
      i = ((*i % 3) == 0) ? (vector.insert(++i, 3, 1) + 3) : ++i;
    }
  }

  print(vector);
}
