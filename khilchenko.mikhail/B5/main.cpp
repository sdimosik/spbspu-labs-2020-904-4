#include <iostream>
#include <stdexcept>

void task1();
void task2();

int main(int argc, char* argv[])
{
  try
  {
    if(argc != 2)
    {
      throw std::invalid_argument("Invalid amount of entry parameters");
    }
    if(std::stoi(argv[1]) == 1)
    {
      task1();
    }
    else if (std::stoi(argv[1]) == 2)
    {
      task2();
    }
    else
    {
      throw std::invalid_argument("Invalid number of the task");
    }
  }
  catch(std::exception& ex)
  {
    std::cerr << ex.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error\n";
    return 2;
  }
  return 0;
}
