#include <iostream>
#include <algorithm>
#include <iterator>
#include "factorial.hpp"

void task2(std::ostream& out)
{
  const size_t size = 10;
  FactorialContainer factorial(size);
  std::copy(factorial.begin(), factorial.end(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';
  std::copy(factorial.rbegin(), factorial.rend(), std::ostream_iterator<size_t>(out, " "));
  out << '\n';
}
