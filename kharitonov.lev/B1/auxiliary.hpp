#ifndef AUXILIARY_HPP
#define AUXILIARY_HPP

#include <algorithm>
#include <iostream>
#include <functional>
#include <cstring>
#include <stdexcept>
#include "access.hpp"


template <typename T>
std::function<bool(const T&, const T&)> orderComparator(const char* order)
{
  if (order == nullptr) {
    throw std::invalid_argument("Null sort order parameter");
  }

  if (std::strcmp(order, "ascending") == 0) {
    return std::less<T>();
  }

  if (std::strcmp(order, "descending") == 0) {
    return std::greater<T>();
  }

  throw std::invalid_argument("Invalid sort order parameter");
}


template <template <class Container> class Access, typename Container>
void sort(Container& container, std::function<bool(typename Container::value_type, typename Container::value_type)> comparator)
{
  const auto begin = Access<Container>::begin(container);
  const auto end = Access<Container>::end(container);
  for (auto i = begin; i != end; i++) 
  {
    auto checkElementIndex = i;
    typename Container::value_type checkElement = Access<Container>::get(container, checkElementIndex);
    for (auto j = i; j != end; j++) 
    {
      typename Container::value_type currentElement = Access<Container>::get(container, j);
      checkElement = Access<Container>::get(container, checkElementIndex);
      if (comparator(currentElement, checkElement)) 
      {
        checkElementIndex = j;
      }
    }
    
    if (checkElementIndex != i)
    {
      std::swap(Access<Container>::get(container, i), Access<Container>::get(container, checkElementIndex));
    }
  }
}

template <typename Container>
void print(const Container& container, const char* separator)
{
  if (separator == nullptr)
  {
    throw std::invalid_argument("Invalid print separator");
  }
  for (const auto& element : container)
  {
    std::cout << element << separator;
  }
}

#endif
