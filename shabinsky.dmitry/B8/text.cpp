#include "text.hpp"

#include <stdexcept>
#include <iostream>

const std::string DASH = "---";
const char SPACE = ' ';
const char END = '\n';

void Text::read(std::istream &in)
{
  char character;
  while (in >> character)
  {
    in >> std::ws;
    if (isalpha(character))
    {
      readWord(in, character);
    }
    else if (character == '-')
    {
      if (isdigit(in.peek()))
      {
        readNumber(in, character);
      }
      else if (in.peek() == '-')
      {
        if (words_.empty())
        {
          throw std::invalid_argument("Invalid input punctuation");
        }
        readPunctuation(in, character);
      }
      else
      {
        throw std::invalid_argument("Invalid input");
      }
    }
    else if ((character == '+' && isdigit(in.peek())) || (isdigit(character)))
    {
      readNumber(in, character);
    }
    else if (ispunct(character))
    {
      if (words_.empty())
      {
        throw std::invalid_argument("Invalid input punctuation");
      }
      readPunctuation(in, character);
    }
    else
    {
      throw std::invalid_argument("Invalid input");
    }
  }
}

void Text::readWord(std::istream &in, char &ch)
{
  Line word;
  word.line += ch;
  word.type = Line::Type::WORD;
  
  while ((isalpha(in.peek())) || (in.peek() == '-'))
  {
    char character;
    in >> character;
    if (character == '-' && in.peek() == '-')
    {
      throw std::invalid_argument("Invalid Word");
    }
    if (word.line.size() == wordWidth)
    {
      throw std::invalid_argument("Word to long");
    }
    word.line += character;
  }
  words_.push_back(word);
}

void Text::readNumber(std::istream &in, char &ch)
{
  Line number;
  number.line += ch;
  number.type = Line::Type::NUMBER;
  
  char decimalSeparator = std::use_facet<std::numpunct<char>>(in.getloc()).decimal_point();
  bool isPointNumber = false;
  
  while (isdigit(in.peek()) || (in.peek() == decimalSeparator))
  {
    char character;
    in >> character;
    if ((number.line.size() == wordWidth) || ((character == decimalSeparator) && isPointNumber))
    {
      throw std::invalid_argument("Invalid input too long");
    }
    if (character == '.')
    {
      isPointNumber = true;
    }
    number.line += character;
  }
  words_.push_back(number);
}

void Text::readPunctuation(std::istream &in, char &ch)
{
  Line punctuation;
  punctuation.line += ch;
  punctuation.type = Line::Type::PUNCTUATION;
  
  if (ch != '-')
  {
    if (words_.back().type == Line::Type::PUNCTUATION)
    {
      throw std::invalid_argument("Invalid input two punctuations");
    }
  }
  else
  {
    char character1 = '\0';
    char character2 = '\0';
    in >> character1 >> character2;
    if (character1 != '-' || character2 != '-')
    {
      throw std::invalid_argument("Invalid dash");
    }
    if (words_.back().type == Line::Type::PUNCTUATION && words_.back().line != ",")
    {
      throw std::invalid_argument("Invalid input dash after punctuation");
    }
    punctuation.line = "---";
  }
  words_.push_back(punctuation);
}

/*void Text::print(std::ostream &out, size_t lineWidth)
{
  size_t countLength = 0;
  using Type = Line::Type;
  
  for (auto it = words_.begin(); it != words_.end(); it = std::next(it))
  {
    std::string word = it->line;
    Type type = it->type;
    
    // last word
    if (it == std::prev(words_.end()))
    {
      lineBreakForPrint(out, countLength, word.size(), lineWidth);
      out << word << std::endl;
    }
      // word is WORD or NUMBER
    else if (type == Type::WORD || type == Type::NUMBER)
    {
      std::string nextWord = it->line;
      Type nextType = it->type;
      lineBreakForPrint(out, countLength, word.size(), lineWidth);
      
      // next word is PUNCTUATION
      if (nextType == Type::PUNCTUATION)
      {
        if (nextWord == "---")
        {
          lineBreakForPrint(out, countLength, word.size() + DASH.size(), lineWidth);
          out << word << SPACE;
          countLength += word.size() + 1;
        }
        else if (((countLength + word.size() + 1) > lineWidth) ||
                 ((type == Type::WORD) &&
                  (countLength + word.size() + DASH.size() + 2 > lineWidth) &&
                  (std::next(it) != std::prev(words_.end())) && (std::next(std::next(it))->line == DASH)))
        {
          out << std::endl;
          countLength = 0;
        }
        out << word;
        countLength += word.size();
        if (!lineBreakForPrint(out, countLength, nextWord.size() + 1, lineWidth))
        {
          out << std::endl;
          countLength++;
        }
      }
      else
      {
        out << word;
        countLength += word.size();
        if (!lineBreakForPrint(out, countLength, std::next(it)->line.size() + 1, lineWidth))
        {
          out << SPACE;
          countLength++;
        }
      }
    }
  }
}*/

void Text::print(std::ostream &out, size_t lineWidth)
{
  using TokenType = Line::Type;
  auto word = words_.begin();
  size_t count = 0;
  
  while (word != words_.end())
  {
    
    if (word == std::prev(words_.end()))
    {
      lineBreakForPrint(out, count, word->line.size(), lineWidth, false);
      out << word->line << END;
    }
    else if (word->type == TokenType::WORD || word->type == TokenType::NUMBER)
    {
      lineBreakForPrint(out, count, word->line.size(), lineWidth, true);
      if (std::next(word)->type == TokenType::PUNCTUATION)
      {
        if (std::next(word)->line == DASH)
        {
          lineBreakForPrint(out, count, word->line.size() + 4, lineWidth, true);
          out << word->line << SPACE;
          count += word->line.size();
          count++;
        }
        else
        {
          if (((count + word->line.size() + 1) > lineWidth)
              || ((count + word->line.size() + 5 > lineWidth)
                  && (std::next(word) != std::prev(words_.end()))
                  && (std::next(std::next(word))->line == DASH)))
          {
            out << END;
            count = 0;
          }
          out << word->line;
          count += word->line.size();
        }
      }
      else
      {
        out << word->line;
        count += word->line.size();
        lineBreakForPrint(out, count, std::next(word)->line.size() + 1, lineWidth);
      }
    }
    else
    {
      out << word->line;
      count += word->line.size();
      lineBreakForPrint(out, count, std::next(word)->line.size() + 1, lineWidth);
    }
    word = std::next(word);
  }
}

bool
Text::lineBreakForPrint(std::ostream &out, size_t &countLength, size_t wordWidthTemp, size_t lineWidth, bool setToZero)
{
  if (countLength + wordWidthTemp > lineWidth)
  {
    out << END;
    setToZero ? countLength = 0 : 0;
    return true;
  }
  return false;
}

bool Text::lineBreakForPrint(std::ostream &out, size_t &countLength, size_t wordWidthTemp, size_t lineWidth)
{
  if ((countLength + wordWidthTemp) > lineWidth)
  {
    out << END;
    countLength = 0;
    return true;
  }
  out << SPACE;
  countLength++;
  return false;
}
