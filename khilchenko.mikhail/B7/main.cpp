#include <stdexcept>
#include <iostream>

void task1();
void task2();

int main(int argc, char* argv[])
{
  try
  {
    if(argc != 2)
    {
      std::invalid_argument("Invalid amount of entry args");
    }
    if(std::stoi(argv[1]) == 1)
    {
      task1();
    }
    else if(std::stoi(argv[1]) == 2)
    {
      task2();
    }
    else
    {
      throw std::invalid_argument("Invalid number of task");
    }
    return 0;
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch(...)
  {
    std::cerr << "Unknown error\n";
    return 2;
  }
}
