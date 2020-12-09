#include "flagGuard.hpp"

FlagGuard::FlagGuard(std::istream &in) : flags_(in.flags()), istream_(in)
{}

FlagGuard::~FlagGuard()
{
  istream_.flags(flags_);
}
