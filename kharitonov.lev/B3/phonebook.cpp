#include "phonebook.hpp"
#include <iostream>
#include <stdexcept>
#include <iterator>

void PhoneBook::insertAfter(iterator iterator, const record_t& record)
{
  book_.insert(std::next(iterator), record);
}

void PhoneBook::insertBefore(iterator iterator, const record_t& record)
{
  book_.insert(iterator, record);
}

void PhoneBook::add(const record_t& record)
{
  book_.push_back(record);
}

PhoneBook::iterator PhoneBook::remove(iterator iterator)
{
  return book_.erase(iterator);
}

bool PhoneBook::isEmpty() const
{
  return book_.empty();
}

PhoneBook::iterator PhoneBook::begin()
{
  return book_.begin();
}

PhoneBook::iterator PhoneBook::end()
{
  return book_.end();
}

PhoneBook::const_iterator PhoneBook::begin() const
{
  return book_.begin();
}

PhoneBook::const_iterator PhoneBook::end() const
{
  return book_.end();
}
