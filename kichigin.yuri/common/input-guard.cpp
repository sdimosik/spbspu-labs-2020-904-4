#include "input-guard.hpp"

InputGuard::InputGuard(std::istream& in):
  istream_(in),
  flags_(in.flags())
{}

InputGuard::~InputGuard()
{
  istream_.flags(flags_);
}
