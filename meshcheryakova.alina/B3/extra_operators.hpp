#ifndef B3_EXTRA_OPERATORS_HPP
#define B3_EXTRA_OPERATORS_HPP

#include <iostream>
#include "commands.hpp"

std::istream& operator >> (std::istream& in, commands::exec_command& command);

namespace commands
{
  struct command_struct
  {
    std::string name;
    std::function<exec_command(std::istream&)> act;
  };

  struct mark_name_str
  {
    std::string& mark_s;
  };

  struct contact_name_str
  {
    std::string& name_s;
  };

  struct number_struct
  {
    std::string& number_s;
  };

  mark_name_str create_mark(std::string& data);
  contact_name_str create_name(std::string& data);
  number_struct create_number(std::string& data);

  std::istream& operator >> (std::istream& in, mark_name_str&& mark);
  std::istream& operator >> (std::istream& in, contact_name_str&& name);
  std::istream& operator >> (std::istream& in, number_struct&& number);
  std::istream& operator >> (std::istream& in, move_position_str& move_pos);
  std::istream& operator >> (std::istream& in, insert_position_str& insert_pos);

}

#endif //B3_EXTRA_OPERATORS_HPP
