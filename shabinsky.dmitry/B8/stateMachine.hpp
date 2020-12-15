#ifndef B8_STATEMACHINE_HPP
#define B8_STATEMACHINE_HPP

#include <iterator>
#include <iostream>

#include "token.hpp"

class StateMachine
{
public:
  const static size_t DEFAULT_WIDTH_LINE;
  const static size_t MIN_WIDTH_LINE;
  const static std::string DASH;
  const static std::string SPACE;
  const static std::string END;
  
  StateMachine(std::ostream &out, size_t lineWidth);
  
  ~StateMachine();
  
  void operator()(Token &);

private:
  const size_t MAX_LINE_WIDTH;
  std::ostream &out_;
  std::string line_;
};

#endif //B8_STATEMACHINE_HPP
