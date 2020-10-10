#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "print.hpp"

void task2(const char *fileName)
{
  std::ifstream in(fileName);

  if (!in.is_open())
  {
    throw std::ios_base::failure("Error: file is not open!\n");
  }

  if (in.peek() == EOF)
  {
    return;
  }

  size_t size = 4;
  using arr_ptr = std::unique_ptr<char[], decltype(&free)>;
  arr_ptr array(static_cast<char *>(malloc(size)), &free);

  size_t quantity = 0;
  while (!in.eof())
  {
    in.read(&array[quantity], size - quantity);
    quantity += in.gcount();

    if (size == quantity)
    {
      size = static_cast<size_t>(size * 1.8);
      arr_ptr arrayTemp(static_cast<char *>(realloc(array.get(), size)), &free);

      if (!arrayTemp)
      {
        throw std::runtime_error("Error: reallocate memory fail\n");
      }
      array.release();
      std::swap(array, arrayTemp);
    }
  }

  in.close();
  std::vector<char> vector(&array[0], &array[quantity]);
  print(vector, false);
}
