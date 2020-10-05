#ifndef TASK2
#define TASK2
#include <fstream>
#include <memory>
#include <vector>
#include "print.hpp"

void task2(const char* file)
{
  std::ifstream input(file);
  if (!input.is_open())
  {
    throw std::runtime_error("File can't be opened");
  }

  const size_t expantion = 128;
  std::unique_ptr<char[], decltype(&std::free)> data(static_cast<char*>(std::malloc(expantion)), std::free);
  size_t index = 0;
  size_t maxSize = expantion;

  if (input.peek() == EOF)
  {
    return;
  }

  while (input >> data[index])
  {
    ++index;
    if (index == maxSize)
    {
      maxSize += expantion;
      std::unique_ptr<char[], decltype(&std::free)> temp(static_cast<char*>(std::realloc(data.get(), maxSize)), std::free);
      if (temp == nullptr)
      {
        throw std::bad_alloc();
      }
      data.release();
      std::swap(data, temp);
    }
  }

  if (input.fail() && !input.eof())
  {
    throw std::runtime_error("Error of reading");
  }

  input.close();
  if (input.is_open())
  {
    throw std::runtime_error("Close of file is failed");
  }

  std::vector<char> vector(&data[0], &data[index]);
  print(vector);
}

#endif // !TASK2
