#include <string>
#include <fstream>
#include <iostream>
#include <memory>
#include <vector>
#include <cstdlib>
#include "tasks.hpp"

void task2(const std::string& data)
{
  std::ifstream input(data);
  if (!input.is_open())
  {
    throw std::runtime_error("File " + data + " is not open");
  }
  if (input.peek() == EOF)
  {
    return;
  }
  size_t size = 0;
  size_t capacity = 128;
  std::unique_ptr<char[], decltype(&std::free)> file(static_cast<char*>(std::malloc(capacity)), std::free);
  while (input >> file[size])
  {
    size++;
    if (size == capacity)
    {
      capacity *= 2;
      std::unique_ptr<char[], decltype(&std::free)> temp(static_cast<char*>(std::realloc(file.get(), capacity)), 
          std::free);
      if (!temp)
      {
        throw std::runtime_error("Impossible to allocate memory for file content");
      }
      file.release();
      file = std::move(temp);
    }
  }
  if (input.fail() && !input.eof())
  {
    throw std::runtime_error("Error while reading file in task 2");
  }
  input.close();
  if (input.is_open())
  {
    throw std::runtime_error("File " + data + " is not closed");
  }
  std::vector<char> content{&file[0], &file[size]};
  print(content, "");
}
