#ifndef B3_MAP_FUNCTION_HPP
#define B3_MAP_FUNCTION_HPP

#include <map>
#include "phoneBook.hpp"
#include "structs.hpp"

using iterator = std::map<std::string, phoneBook::iterator>::iterator;
using map = std::map<std::string, phoneBook::iterator>;

void add (map& mark, phoneBook& book, const phoneBook::contact_str& contact);
void store (map& mark, const std::string& mark_name, const std::string& new_mark_name);
void insert (map& mark, const std::string& mark_name, phoneBook& book, const phoneBook::contact_str& contact, insertPos position);
void remove (map& mark, const std::string& mark_name, phoneBook& book);
void show (map& mark, const std::string& mark_name, std::ostream& out);
void move(map& mark, const std::string& mark_name, int steps);
void move(map& mark, const std::string& mark_name, phoneBook& book, movePos position);
void move_next(map& mark, const std::string& mark_map);
void move_prev(map& mark, const std::string& mark_map);
void replace(map& mark, const std::string& mark_name, const phoneBook::contact_str& contact);

bool is_exist(map& mark, const std::string& mark_name) ;
bool is_correct(map& mark, const std::string& mark_name, phoneBook& book);
iterator get_iterator (map& mark, const std::string& mark_name);

#endif //B3_MAP_FUNCTION_HPP
