#include <iostream>
void task_1(const char* );
void task_2(const char* );
void task_3();
void task_4(const char*, int);

int main(int argc, char *argv[])
{
  try
  {
    int number_of_task = std::stoi(argv[1]);
    if(number_of_task > 4 || number_of_task < 1)
    {
      throw std::invalid_argument(" wrong number of task! \n");
    }
    switch (number_of_task)
    {
      case 1:
        if(argc != 3)
        {
          throw std::invalid_argument(" wrong count of parameters! \n");
        }
        task_1(argv[2]);
        break;
      case 2:
        if(argc != 3)
        {
          throw std::invalid_argument(" wrong count of parameters! \n");
        }
        task_2(argv[2]);
        break;
      case 3:
        if(argc != 2)
        {
          throw std::invalid_argument(" wrong count of parameters! \n");
        }
        task_3();
        break;
      case 4:
        if(argc != 4)
        {
          throw std::invalid_argument(" wrong count of parameters! \n");
        }
        int size = std::stoi(argv[3]);
        task_4(argv[2], size);
        break;
    }
  }
  catch (std::exception& exception)
  {
    std::cerr << exception.what() << "\n";
    return 1;
  }

  return 0;
}




