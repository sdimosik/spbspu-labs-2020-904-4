#ifndef B8_ITERATORINPUT_HPP
#define B8_ITERATORINPUT_HPP

#include <iterator>
#include "token.hpp"

class IteratorInput : public std::iterator<std::input_iterator_tag, Token>
{
public:
  const static size_t MAX_WORD_WIDTH;
  const static std::string DASH;
  
  IteratorInput(std::istream &);
  
  IteratorInput();
  
  Token &operator*();
  
  Token *operator->();
  
  IteratorInput &operator++();
  
  IteratorInput &operator++(int);
  
  bool operator==(const IteratorInput &) const;
  
  bool operator!=(const IteratorInput &) const;

private:
  void read();
  
  void readWord(char &ch);
  
  void readNumber(char &ch);
  
  void readPunctuation(char &ch);
  
  static bool isHalfOfDash(char ch);
  
  std::istream *in_;
  bool someFail_;
  Token token_;
};

#endif //B8_ITERATORINPUT_HPP
