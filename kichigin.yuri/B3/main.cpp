#include <iostream>
#include <string>

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
      break;
    }
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << '\n';
    return 2;
  }
  return 0;
}
