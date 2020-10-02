#ifndef B1_TASK2_HPP
#define B1_TASK2_HPP

#include <fstream>
#include <iostream>
#include <vector>
#include <exception>
#include <memory>
#include "utils.hpp"

namespace task2
{
  void exec(const char *file);
  
  void exec(const char *file)
  {
    std::ifstream fin(file);
    
    if (!fin.is_open())
    {
      throw std::ios_base::failure("File cannot be open!");
    }
    if (fin.peek() == EOF)
    {
      return;
    }
    
    size_t size = 128;
    std::unique_ptr<char[], decltype(&std::free)> data(static_cast<char *>(std::malloc(size)), std::free);
    size_t index = 0;
    
    while (fin >> data[index])
    {
      index++;
      if (index == size)
      {
        size += size;
        std::unique_ptr<char[], decltype(&std::free)> temp(static_cast<char *>(std::realloc(data.get(), size)),
          std::free);
        if (temp == nullptr)
        {
          throw std::bad_alloc();
        }
        data.release();
        std::swap(data, temp);
      }
    }
  
    if (!fin.good() && !fin.eof())
    {
      throw std::ios_base::failure("Fail while reading");
    }
    fin.close();
    if (fin.is_open())
    {
      throw std::runtime_error("Close of file is failed");
    }
    
    std::vector<char> vector(&data[0], &data[index]);
    utils::print(vector, "", false);
  }
}

#endif //B1_TASK2_HPP
