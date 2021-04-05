#include <stdexcept>
#include <iostream>
#include <list>

const size_t MIN_VAL = 1;
const size_t MAX_VAL = 20;
const size_t MAX_SIZE = 20;

void task2(std::istream& in, std::ostream& out)
{
  std::list<int> list;
  size_t currentValue = 0;

  while (in >> currentValue)
  {
    if (list.size() == MAX_SIZE)
    {
      throw std::out_of_range("Number of values out of range");
    }
    if (currentValue < MIN_VAL || currentValue > MAX_VAL)
    {
      throw std::invalid_argument("Value out of bounds");
    }
    list.push_back(currentValue);
  }
  if (!in.eof())
  {
    throw std::runtime_error("Input failed");
  }

  auto begin = list.begin();
  auto end = list.end();

  while (begin != end)
  {
    out << *begin << " ";
    if (++begin == end--)
    {
      break;
    }
    out << *end << " ";
  }
  out << "\n";
}
