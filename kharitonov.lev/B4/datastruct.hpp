#ifndef DATA_STRUCT_HPP
#define DATA_STRUCT_HPP

#include <iostream>
#include <string>

const int MAX_ABS_KEY = 5;

struct DataStruct
{
  int key1;
  int key2;
  std::string str;
};

std::istream& operator>>(std::istream&, DataStruct&);
std::ostream& operator<<(std::ostream&, const DataStruct&);
bool operator<(const DataStruct&, const DataStruct&);

#endif
