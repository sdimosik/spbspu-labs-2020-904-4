#include "point.hpp"

class PointScopeGuard
{
public:
  PointScopeGuard(std::istream& initialIn):
    in(initialIn)
  {
    formatFlags = initialIn.flags();
  }
  ~PointScopeGuard()
  {
    in.flags(formatFlags);
  }
private:
  std::istream& in;
  std::ios_base::fmtflags formatFlags;
};

std::istream& skipWhitespaces(std::istream& in)
{
  while(std::isblank(in.peek()))
  {
    in.ignore();
  }
  return in;
}

std::istream& operator>>(std::istream& in, Point& point)
{
  PointScopeGuard pointScopeGuard(in);
  in.unsetf(std::ios_base::skipws);
  const char leftParenthesis = '(';
  const char rightParenthesis = ')';
  const char semicolon = ';';
  char delimiter = '\0';
  in >> skipWhitespaces >> delimiter;
  if(delimiter != leftParenthesis)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> skipWhitespaces >> point.x >> skipWhitespaces >> delimiter;
  if(delimiter != semicolon)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  in >> skipWhitespaces >> point.y >> skipWhitespaces >> delimiter;
  if(delimiter != rightParenthesis)
  {
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  out << '(' << point.x << ';' << point.y << ')';
  return out;
}
