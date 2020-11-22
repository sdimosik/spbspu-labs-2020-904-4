#include "extra_operators.hpp"
#include <algorithm>
#include <istream>
#include <limits>


const auto invalid_command = [](map&, phoneBook&, std::ostream& out){ out << "<INVALID COMMAND>" << '\n'; };

std::istream& operator >> (std::istream& in, commands::exec_command& command)
{
  static const commands::command_struct Commands[] =
  {
    {"add", &commands::parse_add},
    {"store", &commands::parse_store},
    {"insert", &commands::parse_insert},
    {"delete", &commands::parse_delete},
    {"show", &commands::parse_show},
    {"move", &commands::parse_move}
  };

  std::istream::sentry sentry(in);

  if (in.peek() == std::char_traits<char>::eof())
  {
    command = [](map&, phoneBook&, std::ostream&){};
    return in;
  }

  if(sentry)
  {
    std::string command_name;
    in >> std::ws >> command_name;
    auto new_command = std::find_if(std::begin(Commands), std::end(Commands),
                                    [&](const commands::command_struct& command){ return command_name == command.name; });
    if(new_command != std::end(Commands))
    {
      command = new_command->act(in);

      if (in.fail() && !in.eof())
      {
        in.clear();
        if (char(in.unget().peek()) != '\n')
        {
          in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
      }

      if (in.bad() && !in.eof())
      {
        throw std::ios_base::failure("fail in reading stream! \n");
      }
    }
    else
    {
      in.clear();
      if (char(in.unget().peek()) != '\n')
      {
        in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
      command = invalid_command;
    }
  }
  else
  {
    in.clear();
    if (char(in.unget().peek()) != '\n')
    {
      in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    command = invalid_command;
  }

  return in;
}

  std::istream& commands:: operator>>(std::istream &in, commands:: mark_name_str&& mark)
  {
    std::istream::sentry sentry(in);
    in >> std::ws >> mark.mark_s;

    if(sentry)
    {
      auto data = std::find_if(mark.mark_s.begin(), mark.mark_s.end(),
                               [&](auto element){return (!std::isalnum(element) && !(element == '-'));});
      if(data != mark.mark_s.end())
      {
        mark.mark_s.clear();
        in.setstate(std::ios_base::failbit);
        return in;
      }
    }
    return in;
  }

  std::istream& commands::operator >> (std::istream& in, commands::contact_name_str&& name)
  {
    std::istream::sentry sentry(in);
    if(sentry)
    {
      getline(in, name.name_s);
      if (name.name_s.empty())
      {
        in.setstate(std::ios_base::failbit);
        return in;
      }

      name.name_s.erase(0, 1);
      if ((name.name_s.front() != '\"') || (name.name_s.back() != '\"'))
      {
        name.name_s.clear();
        in.setstate(std::ios_base::failbit);
        return in;
      }
      name.name_s.erase(std::remove(name.name_s.begin(), name.name_s.end(), '\\'), name.name_s.end());
      name.name_s.erase(0, 1);
      name.name_s.pop_back();
      return in;
    }
    return in;
  }

  std::istream& commands::operator >> (std::istream& in, commands::number_struct&& number)
  {
    std::istream::sentry sentry(in);
    if(sentry)
    {
      in >> std::ws >>number.number_s;

      if(number.number_s.empty())
      {
        in.setstate(std::ios_base::failbit);
        return in;
      }
      for (const auto &num : number.number_s)
      {
        if (!isdigit(num))
        {
          number.number_s.clear();
          in.setstate(std::ios_base::failbit);
          return in;
        }
      }
    }
    return in;
  }

  std::istream& commands::operator >> (std::istream& in, commands::move_position_str& move_pos)
  {
    std::istream::sentry sentry(in);
    static const commands::move_position_str Moves[]=
    {
      {"first", movePos:: FIRST},
      {"last", movePos:: LAST}
    };

    if(sentry)
    {
      std::string new_position;
      in >> std::ws >> new_position;
      auto move = std::find_if(std::begin(Moves), std::end(Moves),
                             [&](const move_position_str& move_position){ return new_position == move_position.name;});
      if(move != std::end(Moves))
      {
        move_pos = *move;
      }
      else
      {
        char* p_end;
        int steps = std::strtol(new_position.c_str(), &p_end, 10);
        if(new_position.c_str()[0] != '0' && steps == 0)
        {
          in.setstate(std::ios_base::failbit);
          return in;
        }
        else
        {
          move_pos = {"", steps};
        }
      }
    }

    return in;
  }

  std::istream& commands::operator >> (std::istream& in, commands::insert_position_str& insert_pos)
  {
    std::istream::sentry sentry(in);
    static const commands::insert_position_str Inserts[]=
    {
     {"before", insertPos:: BEFORE},
     {"after", insertPos:: AFTER}
    };

    if(sentry)
    {
      std::string new_insert;
      in >> std::ws >> new_insert;
      auto insert = std::find_if(std::begin(Inserts), std::end(Inserts),
                               [&](const insert_position_str& insert_position){ return new_insert == insert_position.name;});
      if(insert != std::end(Inserts))
      {
        insert_pos = *insert;
      }
      else
      {
        in.setstate(std::ios_base::failbit);
        return in;
      }
    }

    return in;

  }

  commands::mark_name_str commands::create_mark(std::string& data)
  {
    return {data};
  }

  commands::contact_name_str commands::create_name(std::string& data)
  {
    return {data};
  }

 commands:: number_struct commands::create_number(std::string& data)
  {
    return {data};
  }

