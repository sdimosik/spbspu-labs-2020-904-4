#include "tasks.hpp"
#include <stdexcept>
#include <iostream>
#include <fstream>
#include <memory>
#include <vector>

const size_t CAPACITY = 1024;

void task::doSecondTask(const char* fileName)
{
  std::ifstream file(fileName);
  if (!file)
  {
    throw std::invalid_argument("Incorrect argument! File with this name doesn't exist!");
  }

  size_t arraySize = CAPACITY;
  std::unique_ptr<char[], decltype(&free)> array(static_cast<char*>(malloc(CAPACITY)), &free);
  if (!array)
  {
    throw std::runtime_error(UNKNOWN_ERROR);
  }

  size_t currentSize = 0;
  while (file)
  {
    file.read(&array[currentSize], CAPACITY);
    currentSize += file.gcount();

    if (file.gcount() == CAPACITY)
    {
      arraySize += CAPACITY;
      std::unique_ptr<char[], decltype(&free)> tempArray(static_cast<char*>(realloc(array.get(), arraySize)), &free);
      if (!tempArray)
      {
        throw std::runtime_error("Impossible to allocate memory for file content");
      }
      array.release();
      std::swap(array, tempArray);
    }

    if (std::cin.bad())
    {
      throw std::runtime_error("Error while reading");
    }
  }

  std::vector<char> vector(&array[0], &array[currentSize]);
  for (const auto& element : vector)
  {
    std::cout << element;
  }
}
