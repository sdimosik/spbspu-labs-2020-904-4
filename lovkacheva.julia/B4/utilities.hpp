#ifndef UTILITIES_HPP
#define UTILITIES_HPP
#include <vector>
#include "data-struct.hpp"
namespace lovkacheva
{
  int parseKey(const std::string& key);
  int readKey(std::istream &in);
  void skipNonNewlineWs(std::istream &in);
  void readStructs(std::istream &in, std::vector<DataStruct> &dataVector);
  bool greater(const DataStruct& first, const DataStruct& second);
  bool less(const DataStruct &first, const DataStruct &second);
}
#endif
