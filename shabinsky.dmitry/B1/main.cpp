#include <iostream>
#include "task1.hpp"
#include "task2.hpp"
#include "task3.hpp"
#include "task4.hpp"

void checkValid(int argc, char *argv[]);

void execTask(char *argv[]);

int main(int argc, char *argv[])
{
  try
  {
    checkValid(argc, argv);
    execTask(argv);
  }
  catch (const std::exception &exception)
  {
    std::cerr << exception.what() << "\n";
    return 1;
  }
  catch (...)
  {
    std::cerr << "Some problems\n";
    return 2;
  }
  return 0;
}

void checkValid(int argc, char *argv[])
{
  if (argc < 2 || argc > 4)
  {
    throw std::invalid_argument("Incorrect argc. Should be: 2 < argc < 4. Have: " + std::to_string(argc) + "\n");
  }
  
  for (const char symbol : std::string(argv[1]))
  {
    if (symbol < '0' || symbol > '9')
    {
      throw std::invalid_argument("argv[1] isn't digit\n");
    }
  }
  
  int task = std::stoi(argv[1]);
  
  if (task < 1 || task > 4)
  {
    throw std::invalid_argument("Incorrect number task. Should be: 0 < task < 5. Have: " + std::to_string(task) + "\n");
  }
  
  switch (task)
  {
    case 1:
    {
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid count argc for 1 task\n");
      }
      if (std::string(argv[2]) != "ascending" && std::string(argv[2]) != "descending")
      {
        throw std::invalid_argument(
          "Invalid arg for 1 task. Should be: 'ascending' or 'descending'. Have: " + std::string(argv[2]) + "\n");
      }
      break;
    }
    case 2:
    {
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid count argc for 2 task\n");
      }
      int sizeArg = std::string(argv[2]).size();
      if (std::string(argv[2]).substr(sizeArg - 4, 4) != ".txt")
      {
        throw std::invalid_argument("File extension in problem 2 is not equal '.txt'\n");
      }
      break;
    }
    case 3:
    {
      if (argc != 2)
      {
        throw std::invalid_argument("Invalid count argc for 3 task\n");
      }
      break;
    }
    case 4:
    {
      if (argc != 4)
      {
        throw std::invalid_argument("Invalid count argc for 4 task");
      }
      if (std::string(argv[2]) != "ascending" && std::string(argv[2]) != "descending")
      {
        throw std::invalid_argument( "Should be: 'ascending'/'descending'. Have: " + std::string(argv[2]) + "\n");
      }
      for (const char symbol : std::string(argv[3]))
      {
        if (symbol < '0' || symbol > '9')
        {
          throw std::invalid_argument("argv[4] isn't digit\n");
        }
      }
      break;
    }
    default:
    {
    }
  }
}

void execTask(char *argv[])
{
  int task = std::stoi(argv[1]);
  switch (task)
  {
    case 1:
      task1::exec(argv[2]);
      break;
    case 2:
      task2::exec(argv[2]);
      break;
    case 3:
      task3::exec();
      break;
    case 4:
      task4::exec(argv[2], std::stoi(argv[3]));
      break;
    default:
    {
    }
  }
}
