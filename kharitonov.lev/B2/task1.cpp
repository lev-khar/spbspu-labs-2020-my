#include <iostream>
#include <stdexcept>
#include <sstream>
#include <string>
#include "parser.hpp"
#include "queue.hpp"

void task1(std::istream& in, std::ostream& out)
{
  QueueWithPriority<std::string> queue;
  std::string lineCommand;
  while (std::getline(in, lineCommand))
  {
    std::stringstream commandStream(lineCommand);
    if ((commandStream >> std::ws).eof())
    {
      continue;
    }
    Command command = parse(commandStream);
    command(queue, out);
  }
}
