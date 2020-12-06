#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP
#include <string>
#include <iosfwd>
namespace lovkacheva
{
  struct DataStruct
  {
    int key1;
    int key2;
    std::string str;
  };

  std::ostream& operator<<(std::ostream& out, const DataStruct& rhs);
}
#endif
