#ifndef INTERFACE_HPP
#define INTERFACE_HPP

#include <iostream>
#include <string>
#include <unordered_map>
#include "phonebook.hpp"

class PhonebookInterface
{
public:
  PhonebookInterface();
  void add(std::ostream&, const PhoneBook::record_t&);
  void store(std::ostream&, const std::string&, const std::string&);
  void insertBefore(std::ostream&, const std::string&, const PhoneBook::record_t&);
  void insertAfter(std::ostream&, const std::string&, const PhoneBook::record_t&);
  void deleteRecord(std::ostream&, const std::string&);
  void show(std::ostream&, const std::string&) const;
  void moveSteps(std::ostream&, const std::string&, int);
  void moveToBegin(std::ostream&, const std::string&);
  void moveToEnd(std::ostream&, const std::string&);

private:
  PhoneBook phonebook_;
  std::unordered_map<std::string, PhoneBook::iterator> bookmarks_;
  static void printEmpty(std::ostream&);
  static void invalidBookmark(std::ostream&);
  void reassignToBegin();
};

#endif
