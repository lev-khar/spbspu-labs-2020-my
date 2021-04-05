#ifndef PARSER_HPP
#define PARSER_HPP

#include <functional>
#include <iostream>
#include "phonebook.hpp"
#include "interface.hpp"

using Command = std::function<void(PhonebookInterface&, std::ostream&)>;
std::istream& operator>> (std::istream&, Command&);

#endif
