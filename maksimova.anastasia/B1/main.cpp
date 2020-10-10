#include <iostream>

#include "firstTask.hpp"
#include "secondTask.hpp"
#include "thirdTask.hpp"
#include "fourthTask.hpp"

int main(int argc, char* argv[])
{
  try
  {
    int task_number = std::stoi(argv[1]);
    if(task_number < 1 || task_number > 4)
    {
      throw std::invalid_argument("Incorrect task number!\n");
    }
    switch (task_number)
    {
    case 1:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid count of arguments!");
      }
      firstTask(argv[2]);
      break;
    case 2:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid count of arguments!");
      }
      secondTask(argv[2]);
      break;
    case 3:
      if (argc != 2)
      {
        throw std::invalid_argument("Invalid count of arguments!");
      }
      thirdTask();
      break;
    case 4:
      if (argc != 4)
      {
        throw std::invalid_argument("Invalid count of arguments!");
      }
      fourthTask(argv[2], std::stoi(argv[3]));
      break;
      return 0;
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
