#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include <iostream>
#include <string>
#include "queue.hpp"

using ElementPriority = QueueWithPriority<std::string>::ElementPriority;
void add(QueueWithPriority<std::string>&, const std::string&, ElementPriority);
void get(QueueWithPriority<std::string>&, std::ostream&);
void accelerate(QueueWithPriority<std::string>&);
void invalidCommand(std::ostream&);

#endif 
