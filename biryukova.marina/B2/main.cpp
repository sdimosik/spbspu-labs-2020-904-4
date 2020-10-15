#include <iostream>
#include <stdexcept>

void task1();
void task2();

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      std::cerr << "Invalid count of arguments\n";
      return 1;
    }
    int taskNumber = atoi(argv[1]);
    switch (taskNumber)
    {
    case 1:
    {
      task1();
      break;
    }
    case 2:
    {
      task2();
      break;
    }
    default:
    {
      std::cerr << "Invalid task number\n";
      return 1;
    }
    }
  }
  catch (std::invalid_argument& error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  catch (std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return 2;
  }
  return 0;
}
