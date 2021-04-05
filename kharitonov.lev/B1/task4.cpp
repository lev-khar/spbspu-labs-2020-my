#include <stdexcept>
#include <cstdlib>
#include <vector>
#include "auxiliary.hpp"
#include "access.hpp"

void fillRandom(double* array, size_t size)
{
  if (array == nullptr)
  {
    throw std::invalid_argument("Nullpointer to array");
  }
  for (size_t i = 0; i < size; i++)
  {
    array[i] = -1. + static_cast<double>(rand()) / (RAND_MAX / 2);
  }
}

void task4(std::function<bool(const double&, const double&)> comparator, size_t size)
{
  std::vector<double> vector(size);
  fillRandom(vector.data(), size);
  print(vector, " ");
  std::cout << '\n';
  sort<BracketsAccess>(vector, comparator);
  print(vector, " ");
}
