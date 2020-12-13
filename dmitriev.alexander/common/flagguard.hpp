#ifndef FLAGGUARD_HPP
#define FLAGGUARD_HPP

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

#endif
