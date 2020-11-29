#include "data_struct.hpp"
#include "detail.hpp"

bool DataStruct::operator<(const DataStruct &data) const
{
  if(key1 < data.key1)
  {
    return true;
  }

  if(key1 == data.key1)
  {
    if(key2 < data.key2)
    {
      return true;
    }
    else if(key2 == data.key2 && str.length() < data.str.length())
    {
      return true;
    }
  }
  return false;
}

std::istream& operator >>(std::istream& in, DataStruct& data)
{
  if (in.peek() == std::char_traits<char>::eof())
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  int key;
  in >> key >> blank;
  if(key < -5 || key > 5)
  {
    throw std::invalid_argument(" number must be in interval from -5 to 5 ! \n");
  }
  data.key1 = key;
  if(in.peek() != ',')
  {
    in.setstate(std::ios_base:: failbit);
    return in;
  }
  in.ignore(1);
  in >> blank >> key >> blank;
  if(key < -5 || key > 5)
  {
    throw std::invalid_argument(" number must be in interval from -5 to 5 ! \n");
  }
  if(in.peek() != ',')
  {
    in.setstate(std::ios_base::failbit);
    return in;
  }
  in.ignore(1);
  data.key2 = key;
  std::string str;
  getline(in, str);
  data.str = str;
  return in;
}

std::ostream& operator <<(std::ostream& out, const DataStruct& data)
{
  out << data.key1 << "," << data.key2 << "," << data.str;
  return out;
}

