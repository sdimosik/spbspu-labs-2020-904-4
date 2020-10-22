#include <iostream>
#include "secondTask.hpp"
#include "firstTask.hpp"
#include "QueueWithPriority.hpp"

int main(int argc, char* argv[])
{
  try
  {
    if (argc != 2)
    {
      throw std::invalid_argument("Invalid count of arguments!");
    }
    int task_number = std::stoi(argv[1]);
    if(task_number < 1 || task_number > 2)
    {
      throw std::invalid_argument("Incorrect task number!\n");
    }
    switch (task_number)
    {
    case 1:
      firstTask();
      break;
    case 2:
      secondTask();
      break;
    }
  }
  catch (const std::exception& ex)
  {
    std::cerr << ex.what();
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error." << '\n';
    return -1;
  }
}
