#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>

#include "datastruct.hpp"
#include "readutils.hpp"

void task(std::istream& in, std::ostream& out)
{
  std::istream_iterator<DataStruct> inputIterator(in);
  std::istream_iterator<DataStruct> endIterator;
  std::vector<DataStruct> vector(inputIterator, endIterator);

  if (!in.eof()) {
    throw std::runtime_error("Input error");
  }

  if (!vector.empty()) {
    std::sort(vector.begin(), vector.end());
    std::copy(vector.begin(), vector.end(), std::ostream_iterator<DataStruct>(out, "\n"));
  }
}
