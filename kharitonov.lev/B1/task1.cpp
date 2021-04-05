#include <stdexcept>
#include <iostream>
#include <forward_list>
#include <vector>
#include "access.hpp"
#include "auxiliary.hpp"


void task1(std::function<bool(const int&, const int&)> comparator)
{
  std::vector<int> inputVector;
  int inputNumber = 0;
  while (std::cin >> inputNumber)
  {
    inputVector.push_back(inputNumber);
  }
  if (!std::cin.eof())
  {
    throw std::runtime_error("Input failed");
  }
  if (inputVector.empty())
  {
    return;
  }

  std::vector<int> copiedVector(inputVector);
  std::forward_list<int> linkedList(inputVector.begin(), inputVector.end());

  sort<BracketsAccess>(inputVector, comparator);
  sort<AtMethodAccess>(copiedVector, comparator);
  sort<IteratorAccess>(linkedList, comparator);

  print(inputVector, " ");
  std::cout << '\n';
  print(copiedVector, " ");
  std::cout << '\n';
  print(linkedList, " ");
  std::cout << '\n';
}
