#ifndef DATA_SRUCT
#define DATA_SRUCT

#include <string>
#include <iosfwd>

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream& in, DataStruct& dataStruct);
std::ostream& operator<<(std::ostream& out, const DataStruct& dataStruct);
bool operator<(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept;
bool operator>(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept;
bool operator==(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept;
bool operator<=(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept;
bool operator>=(const DataStruct& dataStruct1, const DataStruct& dataStruct2) noexcept;

void print(const DataStruct& dataStruct);

#endif // !DATA_SRUCT
