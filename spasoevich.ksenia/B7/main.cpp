#include <iostream>

void task1();
void task2();

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of arguments");
    }

    char* end;
    int task = std::strtol(argv[1], &end, 10);
    if (!end || task > 2 || task < 1)
    {
      throw std::invalid_argument("Invalid task number");
    }

    task == 1 ? task1() : task2();
  }

  catch (const std::exception& exc)
  {
    std::cerr << exc.what() << "\n";
    return 1;
  }
}
