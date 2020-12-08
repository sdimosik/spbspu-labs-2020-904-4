#ifndef FLAG_SAVER_HPP
#define FLAG_SAVER_HPP
#include <istream>

class FlagSaver 
{
public:
  FlagSaver(std::istream& in);
  ~FlagSaver();
private:
  std::istream& in_;
  std::ios_base::fmtflags flags_;
};

#endif
