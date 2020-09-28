#include <list>
#include <vector>
#include "sort.hpp"
#include "print.cpp"
#include "type.hpp"

void task_1(const char* direction)
{
  std::function<bool(int, int)> compare = get_compare<int>(direction);
  std::vector<int> vector_bracket;

  int i = 0;
  while(std::cin >> i)
  {
    vector_bracket.push_back(i);
  }

  if(!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("fail in reading stream \n");
  }
  if(vector_bracket.empty())
  {
      return;
  }

  std::vector<int> vector_at;
  std::list<int> list_iter;
  copy(vector_bracket.begin(), vector_bracket.end(), back_inserter(vector_at));
  copy(vector_bracket.begin(), vector_bracket.end(), back_inserter(list_iter));

  func_sort<type_bracket>(vector_bracket, compare);
  func_sort<type_at>(vector_at, compare);
  func_sort<type_iter>(list_iter, compare);

  print(vector_bracket);
  print(vector_at);
  print(list_iter);

}
