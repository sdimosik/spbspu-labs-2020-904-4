#include <list>
#include <iostream>
void print_result(std::list<int>::iterator iter_begin, std::list<int>::iterator iter_end);
void print_list(std::list<int>& list)
{
  print_result(list.begin(), --list.end());
  std::cout << '\n';
}

void print_result(std::list<int>::iterator iter_begin, std::list<int>::iterator iter_end)
{
  if(std::distance(iter_begin, iter_end) > 1)
  {
    std::cout << *iter_begin << " " << *iter_end << " ";
    print_result(++iter_begin, --iter_end);
  }
  else if(iter_begin == iter_end)
  {
    std::cout << *iter_begin;
  }
  else
  {
    std::cout << *iter_begin << " " << *iter_end << " ";
  }
}
