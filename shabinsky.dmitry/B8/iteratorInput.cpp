#include "iteratorInput.hpp"

const size_t IteratorInput::MAX_WORD_WIDTH = 20;
const std::string IteratorInput::DASH = "---";

IteratorInput::IteratorInput(std::istream &in) :
  in_(&in),
  someFail_(false)
{
  read();
}

IteratorInput::IteratorInput() :
  in_(nullptr),
  someFail_(true)
{}

Token &IteratorInput::operator*()
{
  return token_;
}

Token *IteratorInput::operator->()
{
  return &token_;
}

IteratorInput &IteratorInput::operator++()
{
  read();
  return *this;
}

IteratorInput &IteratorInput::operator++(int)
{
  auto tmp = this;
  read();
  return *tmp;
}

bool IteratorInput::operator==(const IteratorInput &it) const
{
  return (someFail_ == it.someFail_) && (someFail_ || in_ == it.in_);
}

bool IteratorInput::operator!=(const IteratorInput &it) const
{
  return !(operator==(it));
}

void IteratorInput::read()
{
  char character,
    nextCharter;
  
  *in_ >> std::ws >> character;
  if (in_->fail())
  {
    someFail_ = true;
    return;
  }
  nextCharter = in_->peek();
  
  if (isalpha(character))
  {
    readWord(character);
  }
  else if (isHalfOfDash(character))
  {
    if (isdigit(nextCharter))
    {
      readNumber(character);
    }
    else if (isHalfOfDash(nextCharter))
    {
      if (token_.empty())
      {
        throw std::invalid_argument("Invalid input punctuation");
      }
      readPunctuation(character);
    }
    else
    {
      throw std::invalid_argument("Invalid input");
    }
  }
  else if ((character == '+' && isdigit(nextCharter)) || (isdigit(character)))
  {
    readNumber(character);
  }
  else if (ispunct(character))
  {
    if (token_.empty())
    {
      throw std::invalid_argument("Invalid input punctuation");
    }
    readPunctuation(character);
  }
  else
  {
    throw std::invalid_argument("Invalid input");
  }
}

void IteratorInput::readWord(char &ch)
{
  Token word;
  word.line += ch;
  word.type = Token::Type::WORD;
  char nextCharacter = in_->peek();
  
  while ((isalpha(nextCharacter)) || isHalfOfDash(nextCharacter))
  {
    char character;
    *in_ >> character;
    nextCharacter = in_->peek();
    
    if (isHalfOfDash(character) && isHalfOfDash(nextCharacter))
    {
      throw std::invalid_argument("Invalid Word");
    }
    if (word.line.size() == MAX_WORD_WIDTH)
    {
      throw std::invalid_argument("Word to long");
    }
    word.line += character;
  }
  token_ = word;
}

void IteratorInput::readNumber(char &ch)
{
  Token number;
  number.line += ch;
  number.type = Token::Type::NUMBER;
  
  char decimalSeparator = std::use_facet<std::numpunct<char>>(in_->getloc()).decimal_point();
  bool isPoint = false;
  char nextCharacter = in_->peek();
  
  while (isdigit(nextCharacter) || (nextCharacter == decimalSeparator))
  {
    char character;
    *in_ >> character;
    nextCharacter = in_->peek();
    
    if ((number.line.size() == MAX_WORD_WIDTH) || ((character == decimalSeparator) && isPoint))
    {
      throw std::invalid_argument("Invalid input too long");
    }
    if (character == decimalSeparator)
    {
      isPoint = true;
    }
    number.line += character;
  }
  token_ = number;
}

void IteratorInput::readPunctuation(char &ch)
{
  Token punctuation;
  punctuation.line += ch;
  punctuation.type = Token::Type::PUNCTUATION;
  
  if (!isHalfOfDash(ch))
  {
    if (token_.type == Token::Type::PUNCTUATION)
    {
      throw std::invalid_argument("Invalid input two punctuations");
    }
  }
  else
  {
    char character1 = '\0';
    char character2 = '\0';
    *in_ >> character1 >> character2;
    
    if (!isHalfOfDash(character1) || !isHalfOfDash(character2))
    {
      throw std::invalid_argument("Invalid dash");
    }
    if (token_.type == Token::Type::PUNCTUATION && token_.line != ",")
    {
      throw std::invalid_argument("Invalid input dash after punctuation");
    }
    punctuation.line = DASH;
  }
  token_ = punctuation;
}

bool IteratorInput::isHalfOfDash(char ch)
{
  return ch == '-';
}
