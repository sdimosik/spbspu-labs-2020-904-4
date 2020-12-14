#ifndef TEXT_HANDLER_HPP
#define TEXT_HANDLER_HPP

#include <iosfwd>
#include <vector>
#include "line.hpp"

class Text
{
public:
  void read(std::istream &in);
  
  void print(std::ostream &out, size_t lineWidth);

private:
  void readWord(std::istream &in, char &ch);
  
  void readNumber(std::istream &in, char &ch);
  
  void readPunctuation(std::istream &in, char &ch);
  
  bool
  lineBreakForPrint(std::ostream &out, size_t &countLength, size_t wordWidthTemp, size_t lineWidth, bool setToZero);
  
  bool lineBreakForPrint(std::ostream &out, size_t &countLength, size_t wordWidthTemp, size_t lineWidth);
  
  std::vector<Line> words_;
  const size_t wordWidth = 20;
};

#endif
