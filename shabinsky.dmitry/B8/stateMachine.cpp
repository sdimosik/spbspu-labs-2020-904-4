#include "stateMachine.hpp"

const size_t StateMachine::DEFAULT_WIDTH_LINE = 40;
const size_t StateMachine::MIN_WIDTH_LINE = 25;
const std::string StateMachine::DASH = "---";
const std::string StateMachine::SPACE = " ";
const std::string StateMachine::END = "\n";

StateMachine::StateMachine(std::ostream &out, size_t lineWidth) :
  MAX_LINE_WIDTH(lineWidth),
  out_(out),
  line_()
{}

StateMachine::~StateMachine()
{
  if (!line_.empty())
  {
    out_ << line_ << END;
  }
}

void StateMachine::operator()(Token &token)
{
  using Type = Token::Type;
  std::string word = token.line;
  Type type = token.type;
  
  if (type == Type::WORD || type == Type::NUMBER)
  {
    if (line_.size() + word.size() + SPACE.size() > MAX_LINE_WIDTH)
    {
      out_ << line_ << END;
      line_.clear();
    }
    else if (!line_.empty())
    {
      line_ += SPACE;
    }
    line_ += token.line;
  }
  else
  {
    if ((word == DASH && (line_.size() + DASH.size() + SPACE.size() > MAX_LINE_WIDTH))
        || (((line_.size() + SPACE.size()) > MAX_LINE_WIDTH)))
    {
      size_t lastWhiteSpace = line_.find_last_of(SPACE);
      size_t amountOddChars = line_.size() - lastWhiteSpace;
      std::string temp = line_.substr(lastWhiteSpace, amountOddChars);
      line_.erase(lastWhiteSpace, amountOddChars);
      temp.erase(0, 1);
      out_ << line_ << END;
      line_ = temp;
    }
    if (word == DASH)
    {
      line_ += SPACE;
    }
    line_ += token.line;
  }
}
