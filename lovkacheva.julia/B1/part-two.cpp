#include "parts.hpp"
#include <string>
#include <fstream>
#include <vector>
#include <memory>
#include <cmath>
#include <cstring>
#include "print-contents.hpp"

void lovkacheva::partTwo(std::string filename)
{
  std::ifstream file(filename);
  if (!file.is_open())
  {
    throw std::runtime_error("The file " + filename + " could not be opened");
  }
  if (file.peek() == EOF)
  {
    return;
  }
  size_t arraySize = 0;
  size_t arrayCapacity = 8;
  std::unique_ptr<char[],
      decltype(std::free) *> array(static_cast<char *>(calloc(arrayCapacity, sizeof(char))), std::free);
  if (array == nullptr)
  {
    throw std::bad_alloc();
  }
  file >> std::noskipws;
  while (!file.eof())
  { 
    if (arrayCapacity == arraySize)
    {
      const double GROWTH_FACTOR = 1.6;
      size_t newCapacity = static_cast<size_t>(floor(arrayCapacity * GROWTH_FACTOR));
      std::unique_ptr<char[],
          decltype(std::free) *> temp(static_cast<char *>(realloc(array.get(), newCapacity)), std::free);
      if (temp == nullptr)
      {
        throw std::bad_alloc();
      }
      memset(&temp[arrayCapacity], 0, newCapacity - arrayCapacity);
      array.release();
      std::swap(array, temp);
      arrayCapacity = newCapacity;
    }
    file >> array[arraySize];   
    if (!file.eof())
    {
      if (file.fail())
      {
        throw std::runtime_error("Input error");
      }
      ++arraySize;
    }
  }
  file.close();
  if (file.fail() && !file.eof())
  {
    throw std::runtime_error("The file " + filename + " could not be closed");
  }
  std::vector<char> vector(array.get(), array.get() + arraySize);
  printContents(vector, "", false);
}
