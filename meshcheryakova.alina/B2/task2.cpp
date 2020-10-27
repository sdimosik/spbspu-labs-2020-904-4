#include <iostream>
#include <list>

void print_list(std::list<int>& list);
void task_2()
{
  std::list<int> list;
  int i = 0;
  while(std::cin >> i)
  {
    if(i < 1 || i > 20)
    {
     throw std::invalid_argument(" wrong value of the number! \n");
    }
    else
    {
      if(list.size() < 20)
      {
        list.push_back(i);
      }
      else
      {
        throw std::invalid_argument(" the limit of list size is 20! \n");
      }
    }
  }

  if(!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("fail in reading stream \n");
  }

  if(list.empty())
  {
    return;
  }

  print_list(list);
}
