#ifndef INPUT_GUARD
#define INPUT_GUARD

#include <istream>

class InputGuard
{
public:
  InputGuard(std::istream& in);
  ~InputGuard();
private:
  std::istream& istream_;
  std::ios_base::fmtflags flags_;
};

#endif // !INPUT_GUARD
