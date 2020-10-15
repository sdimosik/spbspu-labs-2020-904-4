#include<iostream>
#include<string>

void task1();
void task2();

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid number of parameters");
    }
    char* end = nullptr;
    const int task = std::strtol(argv[1], &end, 10);
    if ((*end != '\0') || (task < 1) || (task > 2))
    {
      throw std::invalid_argument("Invalid task");
    }
    (task == 1) ? task1() : task2();
  }

  catch (const std::exception& except)
  {
    std::cerr << except.what() << '\n';
    return 1;
  }
}

