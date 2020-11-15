#ifndef COMMANDS
#define COMMANDS

#include<iosfwd>
#include <functional>
#include "book-interface.hpp"
#include "checks.hpp"

namespace details
{
  union MoveParameter
  {
    int steps;
    BookInterface::KeyWord keyWord;
    MoveParameter(int input) :
      steps(input)
    {}
    MoveParameter(const BookInterface::KeyWord& input):
      keyWord(input)
    {}
  };

  enum class UnionParameter
  {
    INVALID,
    STEPS,
    KEY_WORD
  };
}

struct AddCommand
{
  TelephoneBook::Note note;
};

struct StoreCommand
{
  std::string bookmark;
  std::string newBookmark;
};

struct InsertCommand
{
  std::string bookmark;
  std::string position;
  TelephoneBook::Note note;
};

struct DeleteCommand
{
  std::string bookmark;
};

struct ShowCommand
{
  std::string bookmark;
};

struct MoveCommand
{
  using MoveChoice = std::pair<details::UnionParameter, details::MoveParameter>;

  std::string bookmark;
  MoveChoice moveChoice;
};

AddCommand parseAdd(std::istream& istream);
StoreCommand parseStore(std::istream& istream);
InsertCommand parseInsert(std::istream& istream);
DeleteCommand parseDelete(std::istream& istream);
ShowCommand parseShow(std::istream& istream);
MoveCommand parseMove(std::istream& istream);

void executeAdd(AddCommand& command, BookInterface& telephoneBookInterface);
void executeStore(StoreCommand& command, BookInterface& telephoneBookInterface);
void executeInsert(InsertCommand& command, BookInterface& telephoneBookInterface);
void executeDelete(DeleteCommand& command, BookInterface& telephoneBookInterface);
void executeShow(ShowCommand& command, BookInterface& telephoneBookInterface);
void executeMove(MoveCommand& command, BookInterface& telephoneBookInterface);

void add(std::istream& istream, BookInterface& telephoneBookInterface);
void store(std::istream& istream, BookInterface& telephoneBookInterface);
void insert(std::istream& istream, BookInterface& telephoneBookInterface);
void deleteNote(std::istream& istream, BookInterface& telephoneBookInterface);
void show(std::istream& istream, BookInterface& telephoneBookInterface);
void move(std::istream& istream, BookInterface& telephoneBookInterface);

extern std::map<std::string, std::function<void(std::istream& istream, BookInterface& telephoneBookInterface)>> commandList;

#endif // !COMMANDS
