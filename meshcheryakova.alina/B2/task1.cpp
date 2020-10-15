#include <iostream>
#include "queueWithPriority.hpp"
#include "commands.hpp"
#include "details.hpp"

void task_1()
{
  QueueWithPriority<std::string> queue;
  QueueWithPriority<std::string>::ElementPriority tmp_priority;
  Commands tmp_command;

  while(std::cin >> tmp_command)
  {
    std::string line;

    if(tmp_command != WRONG_COMMAND)
    {
      if (tmp_command == ADD)
      {
        std::cin >> tmp_priority;
        if(!input_line_with_spaces(line).empty() && tmp_priority != QueueWithPriority<std::string>::ElementPriority::WRONG_PRIORITY)
        {
          queue.put_element_to_queue(line, tmp_priority);
        }
        else
        {
          std::cout << "<INVALID COMMAND>" << '\n';
        }
      }
      else
      {
        if(input_line_with_spaces(line).empty())
        {
          if(tmp_command == GET)
          {
            if(!queue.is_empty())
            {
              std::string tmp_element;
              queue.get_element_from_queue(tmp_element);
              std::cout << tmp_element << '\n';
            }
            else
            {
              std::cout << "<EMPTY>" << '\n';
            }
          }
          else
          {
            queue.accelerate();
          }
        }
        else
        {
          std::cout << "<INVALID COMMAND>" << '\n';
        }
      }
    }
    else
    {
      std::cout << "<INVALID COMMAND>" << '\n';
    }
  }

  if(!std::cin.eof() && std::cin.fail())
  {
    throw std::ios_base::failure("fail in reading stream \n");
  }

}
