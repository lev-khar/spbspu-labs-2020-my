#ifndef ACCESS_HPP
#define ACCESS_HPP
#include <stdexcept>

template <typename Container>
struct BracketsAccess 
{
  using iterator = typename Container::size_type;
  using element = typename Container::value_type;

  static iterator begin(const Container &) 
  {
    return 0;
  }

  static iterator end(const Container & container) 
  {
    return container.size();
  }

  static element& get(Container & container, const size_t index)
  {
    if (index >= container.size())
    {
      throw std::out_of_range("Element index out of range");
    }
    return container[index];
  }
};

template <typename Container>
struct AtMethodAccess 
{
  using iterator = typename Container::size_type;
  using element = typename Container::value_type;

  static iterator begin(const Container&) 
  {
    return 0;
  }

  static iterator end(const Container& container) 
  {
    return container.size();
  }

  static element& get(Container & container, const size_t index)
  {
    if (index >= container.size())
    {
      throw std::out_of_range("Element index out of range");
    }
    return container.at(index);
  }
};

template <typename Container>
struct IteratorAccess 
{
  using iterator = typename Container::iterator;
  using element = typename Container::value_type;

  static iterator begin(Container & container) 
  {
    return container.begin();
  }

  static iterator end(Container & container) 
  {
    return container.end();
  }

  static element& get(Container &, iterator & iterator)
  {
    return *iterator;
  }
};

#endif
