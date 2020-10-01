#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "print.cpp"

void task_2(const char* name_of_file)
{
  std::ifstream in(name_of_file);
  if(!in.is_open())
  {
    throw std::ios_base::failure("fail while open file \n");
  }

  size_t capacity = 3;
  size_t size = 0;

  using array_ptr = std::unique_ptr<char[], decltype(&free)>;
  array_ptr array(static_cast<char*>(malloc(capacity)), &free);

  while(!in.eof())
  {
    in.read(&array[size], capacity - size);
    size += in.gcount();
    if(size == capacity)
    {
      capacity = static_cast<size_t>(capacity * 1.8);
      array_ptr tmp(static_cast<char*>(realloc(array.get(), capacity)), &free);

      if (tmp)
      {
        array.release();
        std::swap(array, tmp);
      }
      else
      {
        throw std::runtime_error("fail while realloc \n");
      }
    }

  }
  in.close();

  if (in.is_open())
  {
    throw std::ios_base::failure("fail while close file \n");
  }

  std::vector<char> vector(&array[0], &array[size]);
  print(vector, "");
}

