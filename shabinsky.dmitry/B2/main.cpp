#include <iostream>
#include "task1.hpp"
#include "task2.hpp"

void checkValid(int argc, char *argv[]);

void execTask(char *argv[]);

int main(int argc, char *argv[])
{
  try
  {
    checkValid(argc, argv);
    execTask(argv);
    return 0;
  }
  catch (const std::exception &exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem \n";
    return 2;
  }
  
}

void checkValid(int argc, char *argv[])
{
  if (argc != 2)
  {
    throw std::invalid_argument("Invalid number of arguments");
  }
  
  for (const auto &symbol : std::string(argv[1]))
  {
    if (symbol < '0' || symbol > '9')
    {
      throw std::invalid_argument("Invalid task number");
    }
  }
  
  int task = std::stoi(argv[1]);
  
  if (task != 1 && task != 2)
  {
    throw std::invalid_argument("Invalid task number!");
  }
}

void execTask(char *argv[])
{
  int task = std::stoi(argv[1]);
  switch (task)
  {
    case 1:
      task1::exec();
      break;
    case 2:
      task2::exec();
      break;
    default:
    {
    }
  }
}
