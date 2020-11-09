#include <string>
#include <stdexcept>
#include <cctype>
#include <functional>
#include <algorithm>
#include <iostream>
#include "phonebook-interface.hpp"
#include "commands.hpp"

Function printInvalid()
{
  return[](phoneBookInterface&, std::ostream& , std::ostream& errorOutput)
  {
    errorOutput << "<INVALID COMMAND>\n";
  };
}

std::istream& operator >>(std::istream& input, Function& function)
{
  try
  {
    std::string command;
    input >> command;
    if (table.find(command) != table.end())
    {
      function = table.find(command)->second(input);
    }
    else
    {
      function = printInvalid();
    }
  }
  catch (std::invalid_argument& error)
  {
    if (static_cast<std::string>(error.what()) == "<INVALID COMMAND>")
    {
      if (input.unget().peek() != '\n')
      {
        while (input.peek() != '\n')
        {
          input.get();
        }
      }
      function = printInvalid();
    }
    else
    {
      throw;
    }
  }
  return input;
}

std::string getName(std::istream& input)
{
  std::string name;
  input>>name;
 
 if (!input.eof())
  {
    std::string temp;
    std::getline(input, temp);
    name += temp;
  }

  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  if (name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  std::string::iterator iter = std::remove(name.begin(), name.end(), '\\');
  name.erase(iter, name.end());
  name.erase(0, 1);
  name.pop_back();
  return name;
}

std::string getNumber(std::istream& input)
{
  std::string number;
  input>>number; 

  if (number.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  for (size_t i = 0; i < number.size(); i++)
  {
    if (!std::isdigit(number[i]))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }

  return number;
}

std::string getMarkName(std::istream& input)
{
  std::string markName;
  input>>markName;

  if (markName.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }

  for (size_t i = 0; i < markName.size(); i++)
  {
    if (!isalnum(markName[i]) && (markName[i] != '-'))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return markName;
}

Function add(std::istream& input)
{
  std::string number=getNumber(input);
  std::string name=getName(input);

  return[number, name](phoneBookInterface& book, std::ostream&, std::ostream&)
  {
    book.insertAtEnd(number, name);
  };
}

Function store(std::istream& input)
{
  std::string markName=getMarkName(input);
  std::string newMarkName=getMarkName(input);

 return[markName, newMarkName](phoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
  {
    book.add(markName, newMarkName, errorOutput);
  };
}

Function insert(std::istream& input)
{
  std::string direction;
  input>>direction; 
  std::string markName=getMarkName(input);
  std::string number=getNumber(input);
  std::string name=getName(input);

  if (direction == "before")
  {
    return[number, name, markName](phoneBookInterface& book, std::ostream&, std::ostream& Error)
    {
      book.insertBefore(number, name, Error, markName);
    };
  }
  else if (direction == "after")
  {
    return[number, name, markName](phoneBookInterface& book, std::ostream&, std::ostream& Error)
    {
      book.insertAfter(number, name, Error, markName);
    };
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

Function deleteRecord(std::istream& input)
{
  std::string markName=getMarkName(input);

  return[markName](phoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
  {
    book.deleteNote(markName, errorOutput);
  };
}

Function show(std::istream& input)
{
  std::string markName=getMarkName(input);
 return[markName](phoneBookInterface& book, std::ostream& output, std::ostream& errorOutput)
  {
    book.show(output, errorOutput, markName);
  };
}

Function move(std::istream& input)
{
  std::string markName=getMarkName(input);
  std::string num;
  input>>num; 

  return[num, markName](phoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
  {
    book.move(num, errorOutput, markName);
  };
}
