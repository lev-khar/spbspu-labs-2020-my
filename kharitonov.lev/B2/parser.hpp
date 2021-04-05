#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <string>
#include <sstream>
#include <iostream>
#include "queue.hpp"

using ElementPriority = QueueWithPriority<std::string>::ElementPriority;
using Command = std::function<void(QueueWithPriority<std::string>&, std::ostream&)>;
Command parse(std::stringstream&);

#endif
