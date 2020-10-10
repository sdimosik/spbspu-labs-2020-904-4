#include <fstream>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <vector>

const size_t InitialSize = 1024;

void task2(const char* filename)
{
  size_t size = InitialSize;
  std::ifstream inputFile(filename);

  if (!inputFile)
  {
    throw std::ios_base::failure("Failed to open file.");
  }

  std::unique_ptr<char[], decltype(&free)> arr(static_cast<char *> (calloc(size, sizeof(char))), free);

  int i = 0;
  while (inputFile)
  {
    inputFile.read(&arr[i], InitialSize);

    i += inputFile.gcount();

    if (inputFile.gcount() == InitialSize)
    {

      size += InitialSize;
      std::unique_ptr<char[], decltype(&free)> temp(static_cast<char*>(realloc(arr.get(), size)), free);

      if (temp)
      {
        arr.release();
        std::swap(arr, temp);
      }
      else
      {
        throw std::runtime_error("Failed to reallocate.");
      }
    }
  }
  inputFile.close();

  if (inputFile.is_open())
  {
    throw std::ios_base::failure("Failed to close file.");
  }

  std::vector<char> vector(&arr[0], &arr[i]);

  for (const auto& arrayOut : vector)
  {
    std::cout << arrayOut;
  }
}
