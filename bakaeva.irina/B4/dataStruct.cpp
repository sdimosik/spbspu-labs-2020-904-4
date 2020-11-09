#include "dataStruct.hpp"

int extractNumber(std::string &str, std::istream &cin);

std::istream &operator>>(std::istream &cin, DataStruct &data)
{
  if (cin.eof())
  {
    cin.setstate(std::ios_base::failbit);
    return cin;
  }

  std::string str;
  std::getline(cin, str);
  if (str.empty())
  {
    cin.setstate(std::ios_base::failbit);
    return cin;
  }

  data.key1 = extractNumber(str, cin);
  if (cin.fail())
  {
    return cin;
  }

  cin >> std::ws;
  data.key2 = extractNumber(str, cin);
  if (cin.fail())
  {
    return cin;
  }

  cin >> std::ws;
  if (str.empty())
  {
    cin.clear(std::ios_base::failbit);
  }
  data.str = str;

  return cin;
}

std::ostream &operator<<(std::ostream& cout, const DataStruct& data)
{
  cout << data.key1 << "," << data.key2 << "," << data.str;
  return cout;
}
