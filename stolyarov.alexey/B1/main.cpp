#include <iostream>
#include <string>
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

void checkValid(int argc, char* argv[])
{
  if (argc < 2 || argc > 4)
  {
    throw std::invalid_argument("Incorrect task number: " + std::to_string(argc) + "\nShould be 1 < argc < 5\n");
  }

  for (const char symbol : std::string(argv[1]))
  {
    if (symbol < '0' || symbol > '9')
    {
      throw std::invalid_argument("Incorrect format: argv[1] isn't a digit\n");
    }
  }

  int task = std::stoi(argv[1]);

  if (task < 1 || task > 4)
  {
    throw std::invalid_argument("Incorrect task number: " + std::to_string(task) + "\nShould be: 0 < task < 5\n");
  }

  switch (task)
  {
  case 1:
    if (argc != 3)
    {
      throw std::invalid_argument("Incorrect parameter: Invalid count argc for 1 task\n");
    }
    if (std::string(argv[2]) != "ascending" && std::string(argv[2]) != "descending")
    {
      throw std::invalid_argument(
        "Invalid argv for 1 task. Should be: 'ascending' or 'descending'. Have: " + std::string(argv[2]) + "\n");
    }
    break;
  case 2:
    if (argc != 3)
    {
      throw std::invalid_argument("Incorrect parameter: Invalid count argc for 2 task\n");
    }
    break;
  case 3:
    if (argc != 2)
    {
      throw std::invalid_argument("Incorrect parameter: Invalid count argc for 3 task\n");
    }
    break;
  case 4:
    if (argc != 4)
    {
      throw std::invalid_argument("Incorrect parameter: Invalid count argc for 4 task");
    }
    if (std::string(argv[2]) != "ascending" && std::string(argv[2]) != "descending")
    {
      throw std::invalid_argument(
        "Invalid argv for 4 task. Should be: 'ascending' or 'descending'. Have: " + std::string(argv[2]) + "\n");
    }
    for (const char symbol : std::string(argv[3]))
    {
      if (symbol < '0' || symbol > '9')
      {
        throw std::invalid_argument("Incorrect format: argv[4] isn't digit\n");
      }
    }
    break;
  default:
  {}
  }
}

void doTask(char* argv[])
{
  int task = std::stoi(argv[1]);
  switch (task)
  {
  case 1:
    task1(argv[2]);
    break;
  case 2:
    task2(argv[2]);
    break;
  case 3:
    task3();
    break;
  case 4:
    task4(argv[2], std::stoi(argv[3]));
    break;
  default:
  {}
  }
}

int main(int argc, char* argv[])
{
  try
  {
    checkValid(argc, argv);
    doTask(argv);
  }
  catch (const std::exception& exception)
  {
    std::cerr << "ERROR: " << exception.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "ERROR: Unknown error\n";
    return 2;
  }
  return 0;
}
