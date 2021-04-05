#include <iostream>
#include <iterator>
#include <algorithm>
#include "interface.hpp"
#include "parser.hpp"

void task1(std::istream& in, std::ostream& out)
{
  PhonebookInterface interface;
  std::for_each(std::istream_iterator<Command>(in), std::istream_iterator<Command>(), 
      [&interface, &out] (Command command) { command(interface, out); });
}
