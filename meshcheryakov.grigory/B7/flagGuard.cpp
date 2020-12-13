#include "flagGuard.hpp"

FlagGuard::FlagGuard(std::istream &in) :
    in_(in),
    flags_(in.flags())
{}

FlagGuard::~FlagGuard()
{
  in_.flags(flags_);
}
