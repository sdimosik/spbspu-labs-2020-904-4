#include <iostream>
#include <iterator>
#include <map>
#include "commands.hpp"
#include "extra_operators.hpp"
#include "map_function.hpp"

void task_1(std::istream& in, std::ostream& out)
{
  phoneBook book;
  std::map<std::string, phoneBook::iterator> map = {
          {"current", book.begin()}
  };

  std::for_each(std::istream_iterator<commands::exec_command>(in >> std::noskipws), std::istream_iterator<commands::exec_command>(),
                [&](auto& command)
                {
                  command(map, book, out);
                  in >> std::ws;
                });
}
