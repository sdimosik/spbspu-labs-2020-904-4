#include <iostream>
#include <cstring>
#include "parts.hpp"

int main(int argc, char *argv[])
{
  try
  {
    if (argc < 2)
    {
      throw std::invalid_argument("Task number not given, should be 1/2/3/4\n");
    }
    if (strlen(argv[1]) > 1 || argv[1][0] > '4' || argv[1][0] < '1')
    {
      throw std::invalid_argument("Invalid task number, must be 1/2/3/4.");
    }
    switch (std::atoi(argv[1]))
    {
    case 1:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid number of arguments for task 1 (" + std::to_string(argc - 1)
            + " given, 2 needed).");
      }
      lovkacheva::partOne(argv[2]);
      break;
    case 2:
      if (argc != 3)
      {
        throw std::invalid_argument("Invalid number of arguments for task 2 (" + std::to_string(argc - 1)
            + " given, 2 needed).");
      }
      lovkacheva::partTwo(argv[2]);
      break;
    case 3:
      if (argc != 2)
      {
        throw std::invalid_argument("Invalid number of arguments for task 3 (" + std::to_string(argc - 1)
            + " given, 1 needed).");
      }
      lovkacheva::partThree();
      break;
    case 4:
      if (argc != 4)
      {
        throw std::invalid_argument("Invalid number of arguments for task 4 (" + std::to_string(argc - 1)
            + " given, 3 needed).");
      }
      for (char ch : std::string(argv[3]))
      {
        if (!isdigit(ch))
        {
          throw std::invalid_argument("The array size must be a positive number, " + std::string(argv[3]) + " isn't");
        }
      }
      lovkacheva::partFour(argv[2],std::atoi(argv[3]));
      break;
    }
  }
  catch (const std::exception& e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return 1;
  }
  catch (...)
  {
    std::cerr << "Unknown error" << std::endl;
    return 2;
  }
  return 0;
}
