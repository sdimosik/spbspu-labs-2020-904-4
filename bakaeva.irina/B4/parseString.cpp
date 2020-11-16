#include <iostream>

const char COMMA = ',';
const int MIN_NUMBER = -5;
const int MAX_NUMBER = 5;

int extractNumber(std::string &str, std::istream &cin)
{
  size_t pos = str.find(COMMA);

  if (pos == std::string::npos)
  {
    cin.clear(std::ios_base::failbit);
    return 0;
  }

  std::string numberStr = str.substr(0, pos);
  str.erase(0, pos + 1);

  int numberInt;
  try
  {
    numberInt = std::stoi(numberStr, nullptr, 10);
  }
  catch (std::exception const &exc)
  {
    cin.clear(std::ios_base::failbit);
    return 0;
  }

  if ((numberInt < MIN_NUMBER) || (numberInt > MAX_NUMBER))
  {
    cin.clear(std::ios_base::failbit);
    return 0;
  }

  return numberInt;
}
