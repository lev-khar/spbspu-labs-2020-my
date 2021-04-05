#include "parser.hpp"
#include <iostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <sstream>
#include "queue.hpp"
#include "commands.hpp"

const std::unordered_map<std::string, ElementPriority> priorities
{
  {"low", ElementPriority::LOW},
  {"normal", ElementPriority::NORMAL},
  {"high", ElementPriority::HIGH}
};

Command parseAdd(std::stringstream& commandStream)
{
  std::string priority;
  std::string data;
  commandStream >> priority >> std::ws;
  if (!commandStream)
  {
    throw std::runtime_error("Error reading from command stream");
  }
  auto it = priorities.find(priority);
  if (it == priorities.end())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& out)
    {
      invalidCommand(out);
    };
  }
  ElementPriority priorityValue = it->second;
  std::getline((commandStream), data);
  if (data.empty())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& out)
    {
      invalidCommand(out);
    };
  }
  return [data, priorityValue](QueueWithPriority<std::string>& queue, std::ostream&)
  {
    add(queue, data, priorityValue);
  };
}

Command parseGet(std::stringstream& commandStream)
{
  std::string temp;
  std::getline((commandStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& out)
    {
      invalidCommand(out);
    };
  }
  return [](QueueWithPriority<std::string>& queue, std::ostream& out)
  {
    get(queue, out);
  };
}

Command parseAccelerate(std::stringstream& commandStream)
{
  std::string temp;
  std::getline((commandStream >> std::ws), temp);
  if (!temp.empty())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& out)
    {
      invalidCommand(out);
    };
  }
  return [](QueueWithPriority<std::string>& queue, std::ostream&)
  {
    accelerate(queue);
  };
}

const std::unordered_map<std::string, Command(*)(std::stringstream&)> commands
{
  {"add", &parseAdd},
  {"get", &parseGet},
  {"accelerate", &parseAccelerate}
};

Command parse(std::stringstream& commandStream)
{
  std::string command;
  commandStream >> command;
  auto iterator = commands.find(command);
  if (iterator == commands.end())
  {
    return [](QueueWithPriority<std::string>&, std::ostream& out)
    {
      invalidCommand(out);
    };
  }
  else
  {
    return iterator->second(commandStream);
  }
}
