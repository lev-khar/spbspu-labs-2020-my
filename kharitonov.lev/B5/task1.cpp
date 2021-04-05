#include <iostream>
#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <unordered_set>

void task1(std::istream& in, std::ostream& out)
{
  std::istream_iterator<std::string> inputIterator(in);
  std::istream_iterator<std::string> endIterator;
  std::unordered_set<std::string> set(inputIterator, endIterator);

  if (!in.eof()) {
    throw std::runtime_error("Input error");
  }

  std::copy(set.begin(), set.end(), std::ostream_iterator<std::string>(out, "\n"));
}
