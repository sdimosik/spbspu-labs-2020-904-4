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
      throw std::invalid_argument("Invalid number of arguments");
      return 1;
    }
    int tastNumber = atoi(argv[1]);

    switch (tastNumber)
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
    return 1;
  }

  return 0;
}
