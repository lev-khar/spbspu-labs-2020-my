#include "readutils.hpp"
#include <string>
#include <istream>
#include <cctype>

StreamGuard::StreamGuard(std::istream& in) :
  istream_(in),
  flags_(in.flags())
{}
StreamGuard::~StreamGuard()
{
  istream_.flags(flags_);
}

std::istream& skipWs(std::istream& in)
{
  while(!in.eof() && (std::isblank(in.peek())))
  {
    in.get();
  }
  return in;
}
std::istream& skipLine(std::istream& in)
{
  auto state = in.rdstate();
  state &= ~std::ios_base::failbit;
  in.clear(state);
  std::string temp;
  std::getline(in, temp);
  in.clear(state);
  return in;
}
