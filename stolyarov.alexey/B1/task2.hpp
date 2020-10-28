#ifndef TASK_2_HPP
#define TASK_2_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>
#include <memory>
#include "utilities.hpp"

void task2(const char* file)
{
  std::ifstream fin(file);

  if (!fin.is_open())
  {
    throw std::ios_base::failure("Task 2: File cannot be open");
  }
  if (fin.peek() == EOF)
  {
    return;
  }

  size_t size = 128;
  std::unique_ptr<char[], decltype(&std::free)> data(static_cast<char*>(std::malloc(size)), std::free);
  size_t index = 0;

  if (!data)
  {
    throw std::bad_alloc();
  }

  fin >> data[index];

  while (fin)
  {
    index++;
    if (index == size)
    {
      size += size;
      std::unique_ptr<char[], decltype(&std::free)> temp(static_cast<char*>(std::realloc(data.get(), size)),
        std::free);
      if (temp == nullptr)
      {
        throw std::bad_alloc();
      }
      data.release();
      std::swap(data, temp);
    }
    fin >> data[index];
  }

  if (!fin.good() && !fin.eof())
  {
    throw std::ios_base::failure("Task 2: Reading data failure");
  }
  fin.close();
  if (fin.is_open())
  {
    throw std::runtime_error("Task 2: File closing error");
  }

  std::vector<char> vector(&data[0], &data[index]);
  utilities::println(vector, "");
}

#endif
