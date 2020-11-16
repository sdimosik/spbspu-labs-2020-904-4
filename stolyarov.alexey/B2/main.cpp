#include <iostream>
#include <string>
#include "tasks.hpp"

void checkValid(int argc, char* argv[]);

void execTask(char* argv[]);

int main(int argc, char* argv[])
{
  try
  {
    checkValid(argc, argv);
    execTask(argv);
    return 0;
  }
  catch (const std::exception& exception)
  {
    std::cerr << exception.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown problem\n";
    return 2;
  }
}

void checkValid(int argc, char* argv[])
{
  if (argc != 2)
  {
    throw std::invalid_argument("ERROR: Invalid number of arguments");
  }

  for (const auto& symbol : std::string(argv[1]))
  {
    if (symbol != '1' && symbol != '2')
    {
      throw std::invalid_argument("ERROR: Invalid task number: " + std::to_string(symbol) + " Should be 1 or 2\n");
    }
  }
}

void execTask(char* argv[])
{
  int task = std::stoi(argv[1]);
  switch (task)
  {
  case 1:
    task1();
    break;
  case 2:
    task2();
    break;
  }
}
