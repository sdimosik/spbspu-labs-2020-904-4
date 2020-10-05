#include <iostream>
#include <stdexcept>
#include <string>

void task1(const char* direction);
void task2(const char* filename);
void task3();
void task4(const char* direction, size_t size);

int main(int argc, char* argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      std::cerr << "Incorrect amount of arguments.\n";
      return 1;
    }

    char* ptr = nullptr;
    int taskNumber = std::strtol(argv[1], &ptr, 10);
    if (*ptr != 0x00)
    {
      std::cerr << "Incorrect argument.";
      return 1;
    }

    switch (taskNumber)
    {
    case 1:
      if (argc != 3)
      {
        std::cerr << "Incorrect amount of arguments.";
        return 1;
      }

      task1(argv[2]);
      break;

    case 2:
      if (argc != 3)
      {
        std::cerr << "Incorrect amount of arguments.";
        return 1;
      }

      task2(argv[2]);
      break;

    case 3:
      if (argc != 2)
      {
        std::cerr << "Incorrect amount of arguments.";
        return 1;
      }

      task3();
      break;

    case 4:
      if (argc != 4)
      {
        std::cerr << "Incorrect amount of arguments.";
        return 1;
      }

      task4(argv[2], std::stoi(argv[3]));
      break;

    default:
      std::cerr << "Incorrect argument.\n";
      return 1;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';

    return 1;
  }

  return 0;
}
