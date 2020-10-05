#include <fstream>
#include <iostream>
#include <exception>
#include <string>
#include <memory>
#include <vector>

void task2(const char* fileName)
{
  std::ifstream fin (fileName);

  if(!fin.is_open())
  {
    throw std::invalid_argument("File cannot be openned. Filename: " + std::string(fileName));
  }

  size_t size = 10;
  std::unique_ptr< char[], decltype(&free) > array (static_cast<char*>(malloc(size)), free);
  if(array == nullptr)
  {
    throw std::bad_alloc();
  }
  size_t amount = 0;

  while(fin >> array[amount])
  {
    amount++;
    if(size == amount)
    {
      size *= 2;
      std::unique_ptr< char[], decltype(&free) > temp (static_cast<char*>(realloc(array.get(), size)), free);
      if(temp == nullptr)
      {
        throw std::bad_alloc();
      }
      array.release();
      std::swap(array, temp);
    }
  }

  std::vector<char> outPutVector(array.get(), array.get() + amount);
  
  if(!outPutVector.empty())
  {
    for(size_t i = 0; i < amount; i++)
    {
      std::cout << outPutVector[i];
    }
    std::cout << '\n';
  }

  fin.close();

  if(fin.is_open())
  {
    throw std::runtime_error("Failure in closing file. Filename: " + std::string(fileName));
  }
}
