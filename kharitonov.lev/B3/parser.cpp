#include "parser.hpp"
#include <istream>
#include <unordered_map>
#include <string>
#include <cctype>
#include <sstream>
#include "phonebook.hpp"
#include "interface.hpp"
#include "readutils.hpp"

static void invalidCommand(PhonebookInterface, std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}

static void invalidStep(PhonebookInterface, std::ostream& out)
{
  out << "<INVALID STEP>\n";
}

void parseNumber(std::istream& in, std::string& num)
{
  if (!(in >> num))
  {
    return;
  }
  for (char sym : num)
  {
    if (!isdigit(sym))
    {
      in.setstate(std::ios::failbit);
      return;
    }
  }
}
void parseName(std::istream& in, std::string& name)
{
  char sym;
  bool quotations = false;
  if (in.peek() != '\"') {
    in.setstate(std::ios::failbit);
    return;
  }
  in.get();

  while ((in.peek() != '\n') && in.peek() != EOF)
  {
    sym = in.peek();
    if (sym == '\\') 
    {
      in.get();
      if (in.peek() == '\"')
      {
        in.get(sym);
        name.push_back(sym);
      }
    }
    else if (sym == '\"')
    {
      in.get();
      quotations = true;
      break;
    }
    else
    {
      in.get();
      name.push_back(sym);
    }
  }
  if (!quotations)
  {
    in.setstate(std::ios::failbit);
    return;
  }
}
void parseBookmark(std::istream& in, std::string& bookmark)
{
  if (!(in >> bookmark))
  {
    return;
  }
  for (char ch : bookmark)
  {
    if (!isalnum(ch) && ch != '-')
    {
      in.setstate(std::ios::failbit);
      return;
    }
  }
}

static Command parseAdd(std::istream& in)
{
  std::string number;
  in >> skipWs;
  parseNumber(in, number);
  if(in.fail())
  {
    return &invalidCommand;
  }
  std::string name;
  in >> skipWs;
  parseName(in, name);
  if (in.fail())
  {
    return &invalidCommand;
  }
  if (!(in >> std::ws))
  {
    return &invalidCommand;
  }
  PhoneBook::record_t record = { name, number };
  return std::bind(&PhonebookInterface::add, std::placeholders::_1, std::placeholders::_2, record);
}

static Command parseStore(std::istream& in)
{
  std::string oldBookmark;
  in >> skipWs;
  parseBookmark(in, oldBookmark);
  if (in.fail())
  {
    return &invalidCommand;
  }
  std::string newBookmark;
  in >> skipWs;
  parseBookmark(in, newBookmark);
  if (in.fail())
  {
    return &invalidCommand;
  }
  if (!(in >> std::ws))
  {
    return &invalidCommand;
  }
  return std::bind(&PhonebookInterface::store, std::placeholders::_1, std::placeholders::_2, oldBookmark, newBookmark);
}

static Command parseInsert(std::istream& in)
{
  in >> skipWs;
  if (in.peek() == '\n')
  {
    return &invalidCommand;
  }
  std::string pos;
  if ((in >> pos).fail())
  {
    return &invalidCommand;
  }
  std::string bookmark;
  in >> skipWs;
  parseBookmark(in, bookmark);
  if (in.fail())
  {
    return &invalidCommand;
  }
  std::string number;
  in >> skipWs;
  parseNumber(in, number);
  if (in.fail())
  {
    return &invalidCommand;
  }
  std::string name;
  in >> skipWs;
  parseName(in, name);
  if (in.fail())
  {
    return &invalidCommand;
  }
  if (!(in >> std::ws))
  {
    return &invalidCommand;
  }
  PhoneBook::record_t record = { name, number };

  if (pos == "before")
  {
    return std::bind(&PhonebookInterface::insertBefore, std::placeholders::_1, std::placeholders::_2, bookmark, record);
  }
  else if (pos == "after")
  {
    return std::bind(&PhonebookInterface::insertAfter, std::placeholders::_1, std::placeholders::_2, bookmark, record);
  }
  return &invalidCommand;
}

static Command parseDelete(std::istream& in)
{
  std::string bookmark;
  in >> skipWs;
  parseBookmark(in, bookmark);
  if (in.fail())
  {
    return &invalidCommand;
  }
  if (!(in >> std::ws))
  {
    return &invalidCommand;
  }
  return std::bind(&PhonebookInterface::deleteRecord, std::placeholders::_1, std::placeholders::_2, bookmark);
}

static Command parseShow(std::istream& in)
{
  std::string bookmark;
  in >> skipWs;
  parseBookmark(in, bookmark);
  if (in.fail())
  {
    return &invalidCommand;
  }
  if (!(in >> std::ws))
  {
    return &invalidCommand;
  }
  return std::bind(&PhonebookInterface::show, std::placeholders::_1, std::placeholders::_2, bookmark);
}

const std::unordered_map<std::string, void(PhonebookInterface::*)(std::ostream&, const std::string&)> positions{
  {"first", &PhonebookInterface::moveToBegin},
  {"last", &PhonebookInterface::moveToEnd}
};

static Command parseMove(std::istream& in)
{
  std::string bookmark;
  in >> skipWs;
  parseBookmark(in, bookmark);
  if (in.fail())
  {
    return &invalidCommand;
  }
  in >> skipWs;
  if (in.peek() == '\n')
  {
    return &invalidCommand;
  }
  std::string pos;
  if (!(in >> pos))
  {
    return &invalidCommand;
  }
  if (!(in >> std::ws))
  {
    return &invalidCommand;
  }
  auto it = positions.find(pos);
  if (it == positions.end())
  {
    std::stringstream posStream(pos);
    int steps;
    posStream >> steps;
    if (posStream.fail())
    {
      return &invalidStep;
    }
    return std::bind(&PhonebookInterface::moveSteps, std::placeholders::_1, std::placeholders::_2, bookmark, steps);
  }
  else
  {
    return std::bind(it->second, std::placeholders::_1, std::placeholders::_2, bookmark);
  }
}

const std::unordered_map <std::string, Command(*)(std::istream&)> commands{
  {"add", &parseAdd},
  {"store", &parseStore},
  {"insert", &parseInsert},
  {"delete", &parseDelete},
  {"show", &parseShow},
  {"move", &parseMove}
};

std::istream& operator>>(std::istream& in, Command& command)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  in >> std::ws;
  if (in.peek() == EOF)
  {
    in.setstate(std::ios::eofbit);
    return in;
  }
  std::string comName;
  if (!(in >> comName))
  {
    skipLine(in);
    command = &invalidCommand;
    return in;
  }
  auto it = commands.find(comName);
  if (it == commands.end())
  {
    skipLine(in);
    command = &invalidCommand;
    return in;
  }
  command = it->second(in);
  if (!in)
  {
    skipLine(in);
  }
  return in;
}
