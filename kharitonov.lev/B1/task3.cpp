#include <stdexcept>
#include <vector>

#include "auxiliary.hpp"
#include "access.hpp"

void task3()
{
  std::vector<int> vector;
  int inputNumber = 0;

  while (std::cin >> inputNumber)
  {
    if (inputNumber == 0)
    {
      break;
    }
    vector.push_back(inputNumber);
  }

  if (std::cin.fail() && !std::cin.eof()) {
    throw std::runtime_error("Input failed");
  }
  if (vector.empty())
  {
    return;
  }
  if (inputNumber != 0)
  {
    throw std::runtime_error("Input end symbol not found");
  }

  if (vector.back() == 1)
  {
    auto iterator = vector.begin();
    while (iterator != vector.end())
    {
      if (*iterator % 2 == 0)
      {
        iterator = vector.erase(iterator);
      }
      else
      {
        iterator++;
      }
    }
  }

  if (vector.back() == 2) {
    auto iterator = vector.begin();
    while (iterator != vector.end())
    {
      if (*iterator % 3 == 0)
      {
        iterator = vector.insert(++iterator, 3, 1) + 3;
      }
      else
      {
        iterator++;
      }
    }
  }

  print(vector, " ");
}

