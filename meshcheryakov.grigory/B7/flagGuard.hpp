#ifndef SPBSPU_LABS_2020_904_4_FLAGGUARD_HPP
#define SPBSPU_LABS_2020_904_4_FLAGGUARD_HPP

#include <istream>

class FlagGuard
{
public:
  explicit FlagGuard(std::istream &);

  virtual ~FlagGuard();

private:
  std::istream &in_;
  std::ios::fmtflags flags_;

};

#endif
