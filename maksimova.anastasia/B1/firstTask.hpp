#ifndef FIRSTTASK_HPP
#define FIRSTTASK_HPP

#include <iostream>
#include <vector>
#include <forward_list>

#include "access.hpp"
#include "sort.hpp"
#include "print.hpp"

void firstTask(const std::string& type)
{
  std::function<bool(int, int)> compare = get_compare<int>(type.c_str());
  std::vector<int> vec;
  int temp;
  while(std::cin >> temp)
  {
    vec.push_back(temp);
  }
  if(!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("Fail with reading data!\n");
  }
  if(vec.empty())
  {
    return;
  }
  std::vector<int> index_vec(vec);

  sort<index_access>(index_vec, compare);
  print(index_vec);

  std::vector<int> at_vec(vec);
  sort<at_access>(at_vec, compare);
  print(at_vec);

  std::forward_list<int> iter_list(vec.begin(), vec.end());
  sort<iter_access>(iter_list, compare);
  print(iter_list);
}

#endif
