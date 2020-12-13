#ifndef B7_FLAGGUARD_HPP
#define B7_FLAGGUARD_HPP

#include <istream>

class FlagGuard
{
public:
  explicit FlagGuard(std::istream &);
  
  virtual ~FlagGuard();

private:
  std::ios::fmtflags flags_;
  std::istream &istream_;
};

#endif //B7_FLAGGUARD_HPP
