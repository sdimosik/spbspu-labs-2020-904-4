#ifndef USER_INTERFACE_HPP
#define USER_INTERFACE_HPP
#include <unordered_map>
#include <vector>
#include <functional>
#include <memory>
#include "phone-book.hpp"
namespace lovkacheva
{
  class UserInterface
  {
  public:
    UserInterface(const std::shared_ptr<PhoneBook>& PhoneBook);
    using Command = std::function<void()>;
    Command getCommand(std::string &commandLine, std::ostream &out);

    void add(std::vector<std::string> args, std::ostream& out);
    void store(std::vector<std::string> args, std::ostream& out);
    void deleteEntry(std::vector<std::string> args, std::ostream& out);
    void show(std::vector<std::string> args, std::ostream& out);
    void insertEntry(std::vector<std::string> args, std::ostream& out);
    void move(std::vector<std::string> args, std::ostream& out);

  private:
    using BookmarksMap = std::unordered_map<std::string, lovkacheva::PhoneBook::iterator>;
    BookmarksMap bookmarks_;
    std::shared_ptr<PhoneBook> phoneBook_;
  };
}
#endif
