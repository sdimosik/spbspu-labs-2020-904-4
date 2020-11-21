#include "commands.hpp"
#include "extra_operators.hpp"
#include "detail.hpp"
#include <iostream>

const auto invalid_command = [](map&, phoneBook&, std::ostream& out){ out << "<INVALID COMMAND>" << '\n'; };
const auto invalid_steps = [](map&, phoneBook&, std::ostream& out){ out << "<INVALID STEP>" << '\n'; };


commands::exec_command commands::parse_add(std::istream& in)
{
  std::string number;
  std::string name;

  in >> create_number(number) >> create_name(name);

  if(number.empty() || name.empty())
  {
    in.setstate(std::ios_base::failbit);
    return invalid_command;
  }

  phoneBook::contact_str contact = {name, number};
  return [=](map& mark, phoneBook& book, std::ostream&){add(mark, book, contact); };
}

commands::exec_command commands::parse_store(std::istream &in)
{
  std::string mark_name;
  std::string new_mark_name;
  std::string excess;

  in >> create_mark(mark_name) >> create_mark(new_mark_name);
  input_line_with_spaces(in, excess);

  if(mark_name.empty() || new_mark_name.empty() || !excess.empty())
  {
    in.setstate(std::ios_base::failbit);
    return invalid_command;
  }

  return [=](map& mark, phoneBook&, std::ostream& out)
  {
    if(is_exist(mark, mark_name))
    {
      store(mark, mark_name, new_mark_name);
    }
    else
    {
      out << "<INVALID BOOKMARK>" << '\n';
      return;
    }
  };

}

commands::exec_command commands::parse_insert(std::istream& in)
{
  insert_position_str pos;
  std::string mark_name;
  std::string number;
  std::string name;

  in >> pos >> create_mark(mark_name) >> create_number(number) >> create_name(name);

  if(number.empty() || name.empty() || in.fail() || mark_name.empty())
  {
    in.setstate(std::ios_base::failbit);
    return invalid_command;
  }

  phoneBook::contact_str new_contact = {name, number};
  return [=](map& mark, phoneBook& book, std::ostream& out)
  {
    if(!is_exist(mark, mark_name))
    {
      out << "<INVALID BOOKMARK>" << '\n';
      return;
    }
    insert(mark, mark_name, book, new_contact, pos.position);
  };

}

commands::exec_command commands::parse_delete(std::istream& in)
{
  std::string mark_name;
  std::string excess;
  in >> create_mark(mark_name);
  input_line_with_spaces(in, excess);

  if(!excess.empty() || mark_name.empty())
  {
    in.setstate(std::ios_base::failbit);
    return invalid_command;
  }

  return [=](map& mark, phoneBook& book, std::ostream& out)
  {
    if(!is_exist(mark, mark_name))
    {
      out << "<INVALID BOOKMARK>" << '\n';
      return;
    }
    else if(!is_correct(mark, mark_name, book))
    {
      out << "<INVALID COMMAND>" << '\n';
      return;
    }
    else
    {
      remove(mark, mark_name, book);
    }
  };

}
commands::exec_command commands::parse_show(std::istream& in)
{
  std::string mark_name;
  std::string excess;

  in >> create_mark(mark_name);
  input_line_with_spaces(in, excess);

  if(mark_name.empty() || !excess.empty())
  {
    in.setstate(std::ios_base::failbit);
    return invalid_command;
  }

  return [=](map& mark, phoneBook& book, std::ostream& out)
  {
    if(!is_exist(mark, mark_name))
    {
      out << "<INVALID BOOKMARK>" << '\n';
      return;
    }
    else if(book.empty())
    {
      out << "<EMPTY>\n";
      return;
    }
    else if(!is_correct(mark, mark_name, book))
    {
      out << "<INVALID COMMAND>" << '\n';
      return;
    }
    else
    {
      show(mark, mark_name,out);
    }
  };
}

commands::exec_command commands::parse_move(std::istream& in)
{
  std::string mark_name;
  move_position_str moves;
  std::string excess;

  in >> create_mark(mark_name) >> moves ;
  input_line_with_spaces(in, excess);

  if(!excess.empty() || mark_name.empty())
  {
    in.setstate(std::ios_base::failbit);
    return invalid_command;
  }
  if(in.fail())
  {
    return invalid_steps;
  }

  return [=](map& mark, phoneBook& book, std::ostream& out)
  {
    if(!is_exist(mark, mark_name))
    {
      out << "<INVALID BOOKMARK>" << '\n';
      return;
    }
    else if( auto step_pos = boost::get<movePos>(&moves.position))
    {
      move(mark, mark_name, book, *step_pos);
    }
    else
    {
      auto step_int = boost::get<int>(&moves.position);
      move(mark, mark_name, *step_int);
    }
  };
}
