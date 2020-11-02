#include "commands.hpp"
#include <string>
#include <cctype>
#include <stdexcept>
#include <iostream>
#include <functional>
#include <algorithm>
#include "phone-book-interface.hpp"

std::string parseName(std::istream& input)
{
  std::string name;
  input >> name;
  if (!input.eof())
  {
    std::string temp;
    std::getline(input, temp);
    name += temp;
  }
  if (name.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  if ((name.front() != '\"') || (name.back() != '\"'))
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  std::string::iterator iter = std::remove(name.begin(), name.end(), '\\');
  name.erase(iter, name.end());
  name.erase(0, 1);
  name.pop_back();
  return name;
}

std::string parseNumber(std::istream& input)
{
  std::string number;
  input >> number;
  if (number.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  for (size_t i = 0; i < number.size(); i++)
  {
    if (!isdigit(number[i]))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return number;
}

std::string parseMark(std::istream& input)
{
  std::string mark;
  input >> mark;
  if (mark.empty())
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
  for (size_t i = 0; i < mark.size(); i++)
  {
    if ((!isalnum(mark[i])) && (mark[i] != '-'))
    {
      throw std::invalid_argument("<INVALID COMMAND>");
    }
  }
  return mark;
}

FunctionType printInvalid()
{
  return[](PhoneBookInterface&, std::ostream& , std::ostream& errorOutput)
  {
    errorOutput << "<INVALID COMMAND>\n";
  };
}

FunctionType add(std::istream& input)
{
  std::string number = parseNumber(input);
  std::string name = parseName(input);
  return[number, name](PhoneBookInterface& book, std::ostream&, std::ostream&)
  {
    book.insertToEnd(number, name);
  };
}

FunctionType store(std::istream& input)
{
  std::string mark = parseMark(input);
  std::string newMark = parseMark(input);
  return[mark, newMark](PhoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
  {
    book.addBookmark(mark, newMark, errorOutput);
  };
}

FunctionType insertBookmark(std::istream& input)
{
  std::string position;
  input >> position;
  std::string mark = parseMark(input);
  std::string number = parseNumber(input);
  std::string name = parseName(input);
  if (position == BEFORE)
  {
    return[number, name, mark](PhoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
    {
      book.insertBefore(number, name, errorOutput, mark);
    };
  }
  else if (position == AFTER)
  {
    return[number, name, mark](PhoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
    {
      book.insertAfter(number, name, errorOutput, mark);
    };
  }
  else
  {
    throw std::invalid_argument("<INVALID COMMAND>");
  }
}

FunctionType deleteBookmark(std::istream& input)
{
  std::string mark = parseMark(input);
  return[mark](PhoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
  {
    book.deleteBookmark(mark, errorOutput);
  };
}

FunctionType showBookmark(std::istream& input)
{
  std::string mark = parseMark(input);
  return[mark](PhoneBookInterface& book, std::ostream& output, std::ostream& errorOutput)
  {
    book.showBookmark(output, errorOutput, mark);
  };
}

FunctionType move(std::istream& input)
{
  std::string mark = parseMark(input);
  std::string steps;
  input >> steps;
  return[steps, mark](PhoneBookInterface& book, std::ostream&, std::ostream& errorOutput)
  {
    book.move(steps, errorOutput, mark);
  };
}

std::istream& operator >>(std::istream& input, FunctionType& function)
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
