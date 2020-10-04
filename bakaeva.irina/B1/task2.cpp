#include <iostream>
#include <fstream>
#include <memory>
#include <vector>
#include "printData.hpp"

void task2(const char *file)
{
  std::ifstream fin(file);

  if (!fin.is_open())
  {
    throw std::ios_base::failure("File is not open!\n");
  }

  if (fin.peek() == EOF)
  {
    return;
  }

  size_t size = 10;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char *>(malloc(size)), &free);

  size_t count = 0;
  while(!fin.eof())
  {
    fin.read(&array[count], size - count);
    count += fin.gcount();
    size = static_cast<size_t>(size * 1.8);
    std::unique_ptr<char[], decltype(&free)> tempArray(static_cast<char *>(realloc(array.get(), size)), &free);
    if(!tempArray)
    {
      throw std::runtime_error("Can't reallocate memory\n");
    }
    array.release();
    std::swap(array, tempArray);
  }
  fin.close();

  std::vector<char> vector(&array[0], &array[count]);
  printData(vector, "");
}
