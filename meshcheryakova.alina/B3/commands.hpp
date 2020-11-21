#ifndef B3_COMMANDS_HPP
#define B3_COMMANDS_HPP

#include <iostream>
#include <functional>
#include <boost/variant.hpp>
#include "map_function.hpp"
#include "structs.hpp"


namespace commands
{
  using exec_command = std::function<void(map& mark, phoneBook& book, std::ostream&)>;

  struct insert_position_str
  {
    std::string name;
    insertPos position;
  };

  struct move_position_str
  {
    std::string name;
    boost::variant<movePos, int> position;
  };

  exec_command parse_add(std::istream& in);
  exec_command parse_store(std::istream& in);
  exec_command parse_insert(std::istream& in);
  exec_command parse_delete(std::istream& in);
  exec_command parse_show(std::istream& in);
  exec_command parse_move(std::istream& in);
}

#endif //B3_COMMANDS_HPP
