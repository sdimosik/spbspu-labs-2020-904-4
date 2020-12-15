#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

class Token
{
public:
  enum class Type
  {
    WORD,
    NUMBER,
    PUNCTUATION
  };
  
  bool empty() const
  {
    return this->line.empty();
  }
  
  std::string line;
  Type type;
};

#endif
