#include <iostream>
#include <exception>

#include "task.hpp"

int main(int argc, char *argv[])
{
  
  try
  {
    if (argc != 1 && argc != 3)
    {
      throw std::invalid_argument("Invalid number args");
    }
    size_t lineWidth = StateMachine::DEFAULT_WIDTH_LINE;
    if (argc == 3)
    {
      if (std::string(argv[1]) != "--line-width")
      {
        throw std::invalid_argument("Invalid argument");
      }
      if (std::stoi(argv[2]) < static_cast<int>(StateMachine::MIN_WIDTH_LINE))
      {
        throw std::invalid_argument("Invalid argument");
      }
      lineWidth = std::stoi(argv[2]);
    }
    task::exec(lineWidth);
  }
  catch (std::exception &exception)
  {
    std::cerr << exception.what();
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error";
    return 2;
  }
  return 0;
}
