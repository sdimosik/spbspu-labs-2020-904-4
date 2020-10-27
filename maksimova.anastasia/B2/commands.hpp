#ifndef SPBSPU_LABS_2020_904_4_COMMANDS_HPP
#define SPBSPU_LABS_2020_904_4_COMMANDS_HPP

#include <iostream>
#include <sstream>

#include "QueueWithPriority.hpp"

template <typename QueueElement>
void add(QueueWithPriority<QueueElement> &queue, std::istringstream &input, std::ostream &output)
{
    std::string priority;
    input >> priority;
    std::string data;
    input >> data;
    if (!input.eof())
    {
        std::string temp;
        std::getline(input, temp);
        data += temp;
    }
    if (data.empty() || priority.empty())
    {
        output << "<INVALID COMMAND>\n";
        return;
    }
    typename QueueWithPriority<QueueElement>::ElementPriority priority_enum;
    if (priority == "high")
    {
        priority_enum = QueueWithPriority<QueueElement>::ElementPriority::HIGH;
    }
    else if (priority == "normal")
    {
        priority_enum = QueueWithPriority<QueueElement>::ElementPriority::NORMAL;
    }
    else if (priority == "low")
    {
        priority_enum = QueueWithPriority<QueueElement>::ElementPriority::LOW;
    }
    else
    {
        output << "<INVALID COMMAND>\n";
        return;
    }
    queue.PutElementToQueue(data, priority_enum);
}

template <typename QueueElement>
void get(QueueWithPriority<QueueElement> &queue, std::ostream &output)
{
    if(queue.Empty())
    {
        output << "<EMPTY>\n";
    }
    else
    {
        output << queue.GetElementFromQueue() << '\n';
        queue.PopFront();
    }
}

template <typename QueueElement>
void accelerate(QueueWithPriority<QueueElement> &queue)
{
    queue.Accelerate();
}

template <typename QueueElement>
void interpreter(std::istringstream &input, std::ostream &output, QueueWithPriority<QueueElement> &queue)
{
    std::string command;
    input >> command;
    if(command == "add")
    {
        add(queue, input, output);
    }
    else if (command == "get")
    {
        get(queue, output);
    }
    else if(command == "accelerate")
    {
        accelerate(queue);
    }
    else
    {
        output << "<INVALID COMMAND>\n";
    }
}

#endif
