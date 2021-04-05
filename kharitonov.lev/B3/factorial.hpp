#ifndef FACTORIAL_HPP
#define FACTORIALR_HPP

#include <cstddef>
#include <iterator>

class FactorialContainer
{
public:
  class const_iterator : public std::iterator<std::bidirectional_iterator_tag, size_t, ptrdiff_t, size_t*, size_t>
  {
  public:
    value_type operator*() const;

    bool operator==(const const_iterator& iter) const;
    bool operator!=(const const_iterator& iter) const;

    const_iterator& operator++();
    const_iterator& operator--();

    const_iterator operator++(int);
    const_iterator operator--(int);

  private:
    friend FactorialContainer;
    const_iterator(size_t, size_t, size_t, value_type);
    size_t minOperand_;
    size_t maxOperand_;
    size_t operand_;
    value_type value_;
  };
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

  FactorialContainer();
  FactorialContainer(size_t);
  const_iterator begin() const;
  const_iterator end() const;
  const_reverse_iterator rbegin() const;
  const_reverse_iterator rend() const;

private:
  size_t size_;
  size_t maxValue_;
};

#endif
