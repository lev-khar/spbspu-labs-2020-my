#include "commands.hpp"
#include <iostream>
#include <string>
#include "queue.hpp"

void add(QueueWithPriority<std::string>& queue, const std::string& data, ElementPriority priority)
{
  queue.putElementToQueue(data, priority);
}

void get(QueueWithPriority<std::string>& queue, std::ostream& out)
{
  if (queue.isEmpty())
  {
    out << "<EMPTY>\n";
  }
  else
  {
    out << queue.getElementFromQueue() << "\n";
    queue.removeFirst();
  }
}

void accelerate(QueueWithPriority<std::string>& queue)
{
  queue.accelerate();
}

void invalidCommand(std::ostream& out)
{
  out << "<INVALID COMMAND>\n";
}
