#ifndef AUXILIARY_HPP
#define AUXILIARY_HPP

#include <istream>
#include <string>

class StreamGuard
{
public:
  StreamGuard(std::istream&);
  ~StreamGuard();
private:
  std::istream& istream_;
  std::istream::fmtflags flags_;
};

std::istream& skipWs(std::istream&);
std::istream& skipLine(std::istream&);

#endif
