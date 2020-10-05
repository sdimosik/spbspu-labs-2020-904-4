#include <iostream>
#include <string>
#include "first.hpp"
#include "second.hpp"
#include "third.hpp"
#include "fourth.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if ((argc < 2) || (argc > 4))
    {
      throw std::invalid_argument("Invalid count of args!");
    }

    for (const char& ch : std::string(argv[1]))
    {
      if (ch < '0' || ch > '9')
      {
        throw std::invalid_argument("Invalid task number");
      }
    }

    char *p;
    long part = strtol(argv[1], &p, 10);
    if (*p != '\0')
    {
      throw std::invalid_argument("Invalid argument for conversion str to long");
    }

    switch (part)
    {
      case 1:
      {
        if (argc != 3)
        {
          throw std::invalid_argument("Invalid arguments number");
        }

        firstTask(argv[2]);
        break;
      }
      case 2:
      {
        if (argc != 3)
        {
          throw std::invalid_argument("Invalid arguments number");
        }

        secondTask(argv[2]);
        break;
      }
      case 3:
      {
        if (argc != 2)
        {
          throw std::invalid_argument("Invalid arguments number");
        }

        thirdTask();
        break;
      }
      case 4:
      {
        if (argc != 4)
        {
          throw std::invalid_argument("Invalid arguments number");
        }

        for (const char& ch : std::string(argv[3]))
        {
          if (ch < '0' || ch > '9')
          {
            throw std::invalid_argument("Invalid task number");
          }
        }

        char *pTemp;
        long temp = strtol(argv[3], &pTemp, 10);
        if (*pTemp != '\0')
        {
          throw std::invalid_argument("Invalid argument for conversion str to long");
        }

        fourthTask(argv[2], temp);
        break;
      }
      default:
      {
        throw std::invalid_argument("Invalid task number");
      }
    }

    return 0;
  }
  catch (const std::exception& e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem\n";
    return 2;
  }
}
