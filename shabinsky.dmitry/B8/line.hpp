#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>

struct Line
{
  enum class Type
  {
    WORD,
    NUMBER,
    PUNCTUATION
  };
  
  std::string line;
  Type type;
};

#endif
