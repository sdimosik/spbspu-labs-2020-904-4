#include <fstream>
#include <vector>
#include <memory>
#include "extensions.hpp"

void task2(const char *fileName)
{
  std::ifstream fin(fileName);

  if (!fin.is_open())
  {
    throw std::ios_base::failure("Can't find file: " + std::string(fileName));
  }

  size_t size = 16;
  std::unique_ptr<char[], decltype(&std::free)> data(static_cast<char *>(std::malloc(size)), std::free);
  size_t count = 0;

  while (!fin.eof())
  {
    fin.read(&data[count], size - count);
    count += fin.gcount();
    size = static_cast<size_t>(size * 2);
    std::unique_ptr<char[], decltype(&std::free)> temp(static_cast<char *>(std::realloc(data.get(), size)), std::free);
    if (!temp)
    {
      throw std::bad_alloc();
    }
    data.release();
    std::swap(data, temp);
  }
  
  fin.close();

  std::vector<char> vector(data.get(), data.get() + count);

  printArray(vector, "");
}
