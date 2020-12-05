#include <iostream>

void task_1();
void task_2();

int main(int argc, char *argv[])
{
  try
  {
    if(argc != 2)
    {
      throw std::invalid_argument("incorrect number of arguments! \n");
    }
    int number_of_task = std::stoi(argv[1]);
    switch (number_of_task)
    {
      case 1:
        task_1();
        break;
      case 2:
        task_2();
        break;
      default: throw std::invalid_argument("wrong number of task! \n");
    }
  }


  catch (std::exception& exception)
  {
    std::cerr << exception.what() << "\n";
    return 1;
  }
  return 0;
}
