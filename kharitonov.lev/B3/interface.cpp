#include "interface.hpp"
#include <string>
#include <ostream>
#include <algorithm>
#include <iterator>
#include "phonebook.hpp"

PhonebookInterface::PhonebookInterface()
{
  bookmarks_["current"] = phonebook_.end();
}

void PhonebookInterface::add(std::ostream&, const PhoneBook::record_t& record)
{
  const bool firstElem = phonebook_.isEmpty();
  phonebook_.add(record);
  if (firstElem)
  {
    reassignToBegin();
  }
}

void PhonebookInterface::store(std::ostream& out, const std::string& bookmark, const std::string& newBookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    invalidBookmark(out);
  }
  else
  {
    bookmarks_[newBookmark] = it->second;
  }
}

void PhonebookInterface::insertBefore(std::ostream& out, const std::string& bookmark, const PhoneBook::record_t& record)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    invalidBookmark(out);
    return;
  }
  const bool firstElem = phonebook_.isEmpty();
  phonebook_.insertBefore(it->second, record);
  if (firstElem)
  {
    reassignToBegin();
  }
}
void PhonebookInterface::insertAfter(std::ostream& out, const std::string& bookmark, const PhoneBook::record_t& record)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    invalidBookmark(out);
    return;
  }
  const bool firstElem = phonebook_.isEmpty();
  phonebook_.insertAfter(it->second, record);
  if (firstElem)
  {
    reassignToBegin();
  }
}

void PhonebookInterface::deleteRecord(std::ostream& out, const std::string& bookmark)
{
  auto marked = bookmarks_.find(bookmark);
  if (marked == bookmarks_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  auto temp = marked->second;
  for (auto it = bookmarks_.begin(); it != bookmarks_.end(); it++)
  {
    if (it->second == temp)
    {
      if ((std::next(temp) != phonebook_.end()) || (temp == phonebook_.begin()))
      {
        it->second++;
      }
      else
      {
        it->second--;
      }
    }
  }
  phonebook_.remove(temp);
}

void PhonebookInterface::show(std::ostream& out, const std::string& bookmark) const
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  out << it->second->number << " " << it->second->name << "\n";
}

void PhonebookInterface::moveSteps(std::ostream& out, const std::string& bookmark, int steps)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  if(steps > 0)
  {
    const int distEnd = std::distance(it->second, phonebook_.end()) - 1;
    std::advance(it->second, std::min(steps, distEnd));
  }
  if ((steps < 0) && (it->second != phonebook_.begin()))
  {
    const int distBeg = 0 - std::distance(phonebook_.begin(), it->second);
    std::advance(it->second, std::max(steps, distBeg));
  }
}

void PhonebookInterface::moveToBegin(std::ostream& out, const std::string& bookmark)
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  it->second = phonebook_.begin();
}

void PhonebookInterface::moveToEnd(std::ostream& out, const std::string& bookmark) 
{
  auto it = bookmarks_.find(bookmark);
  if (it == bookmarks_.end())
  {
    invalidBookmark(out);
    return;
  }
  if (phonebook_.isEmpty())
  {
    printEmpty(out);
    return;
  }
  it->second = std::prev(phonebook_.end());
}

void PhonebookInterface::reassignToBegin()
{
  auto it = bookmarks_.begin();
  while(it != bookmarks_.end())
  {
    it->second = phonebook_.begin();
    it++;
  }
}

void PhonebookInterface::invalidBookmark(std::ostream& out)
{
  out << "<INVALID BOOKMARK>\n";
}

void PhonebookInterface::printEmpty(std::ostream& out)
{
  out << "<EMPTY>\n";
}
