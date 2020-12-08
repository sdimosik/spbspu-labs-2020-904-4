#include "flagSaver.hpp"

FlagSaver::FlagSaver(std::istream& in) :
  in_(in),
  flags_(in.flags())
{}

FlagSaver::~FlagSaver()
{
  in_.flags(flags_);
}
