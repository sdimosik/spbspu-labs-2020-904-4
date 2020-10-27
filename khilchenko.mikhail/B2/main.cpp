#include <exception>
#include <iostream>

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

    int numberOfTask = std::atoi(argv[1]);

    if(numberOfTask < 1 || numberOfTask > 2)
    {
      throw std::invalid_argument("Invalid number of task");
    }

    switch(numberOfTask)
    {
      case 1:
        task1();
        break;
      case 2:
        task2();
        break;
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
