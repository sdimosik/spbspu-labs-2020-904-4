#ifndef SECONDTASK_HPP
#define SECONDTASK_HPP

#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

void secondTask(const char *file)
{
  std::ifstream fin(file);

  if (!fin.is_open())
  {
    throw std::ios_base::failure("File is not open!\n");
  }
  if(fin.peek() == EOF)
  {
    return;
  }
  size_t size = 16, count = 0;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char *>(malloc(size)), &free);
  while(fin >> array[count])
  {
    ++count;
    if(count == size)
    {
      size *= 2;
      std::unique_ptr<char[], decltype(&free)> array_temp(static_cast<char *>(realloc(array.get(), size)), &free);
      if(!array_temp)
      {
        throw std::bad_alloc();
      }
      array.release();
      std::swap(array, array_temp);
    }
  }
  fin.close();
  if(fin.is_open())
  {
    throw std::ios_base::failure("Fail isn't closed!\n");
  }
  std::vector<char> vec(&array[0], &array[count]);
  for(const auto &item : vec)
  {
    std::cout << item;
  }
  std::cout << '\n';
}

#endif
