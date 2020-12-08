#include <fstream>
#include <memory>
#include <vector>
#include "print.hpp"

void task2(const char *file_name)
{
  std::ifstream fin(file_name);

  if (!fin.is_open())
  {
    throw std::invalid_argument("Error. File can't be opened \n");
  }

  if (fin.peek() == EOF)
  {
    return;
  }

  size_t capacity = 10;
  using arr_ptr = std::unique_ptr<char[], decltype(&free)>;
  arr_ptr array(static_cast<char *>(malloc(capacity)), &free);
  size_t size = 0;

  while (!fin.eof())
  {
    fin.read(&array[size], capacity - size);
    size += fin.gcount();

    if (capacity == size)
    {
      capacity = static_cast<size_t>(capacity * 1.8);
      arr_ptr arr(static_cast<char *>(realloc(array.get(), capacity)), &free);

      if (!arr)
      {
        throw std::invalid_argument("Error. Can't reallocate memory\n");
      }
      array.release();
      std::swap(array, arr);
    }
  }

  fin.close();

  if (fin.is_open())
  {
    throw std::invalid_argument("Error while closing file\n");
  }

  std::vector<char> output_vector(array.get(), &array[size]);
  print(output_vector, "");
}
