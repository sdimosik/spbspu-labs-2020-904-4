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
      throw std::invalid_argument("Invalid count of arguments");
    }
    int taskNumber = atoi(argv[1]);
    switch (taskNumber)
    {
    case 1:
      task1();
      break;
    case 2:
      task2();
      break;
    default:
      throw std::invalid_argument("Invalid task number");
    }
  }
  catch (std::exception& error)
  {
    std::cerr << error.what() << '\n';
    return 1;
  }
  return 0;
}
