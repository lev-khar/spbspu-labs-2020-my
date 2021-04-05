#include "datastruct.hpp"
#include <iostream>
#include <cstdlib>
#include "readutils.hpp"

std::istream& operator>>(std::istream& in, DataStruct& ds)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  in >> std::ws;

  int key1;
  if (!(in >> key1)) 
  {
    return in;
  }
  if (std::abs(key1) > MAX_ABS_KEY)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  char separator;
  if (!(in >> skipWs >> separator))
  {
    return in;
  }
  if ((separator != ',')) {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }

  int key2;
  if (!(in >> skipWs >> key2))
  {
    return in;
  }
  if (std::abs(key2) > MAX_ABS_KEY)
  {
    in.setstate(std::ios::failbit);
    return in;
  }

  if (!(in >> skipWs >> separator))
  {
    return in;
  }
  if (separator != ',') {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }

  std::string str;
  std::getline(in, str);

  if (in.fail()) {
    return in;
  }

  ds = { key1, key2, str };

  return in;
}

std::ostream& operator<<(std::ostream& out, const DataStruct& ds)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << ds.key1 << ", " << ds.key2 << ", " << ds.str;
  }
  return out;
}

bool operator<(const DataStruct& ds1, const DataStruct& ds2)
{
  if (ds1.key1 != ds2.key1)
  {
    return ds1.key1 < ds2.key1;
  }
  if (ds1.key2 != ds2.key2)
  {
    return ds1.key2 < ds2.key2;
  }
  return ds1.str.size() < ds2.str.size();
}
