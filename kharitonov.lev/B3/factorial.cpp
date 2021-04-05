#include "factorial.hpp"
#include <stdexcept>
#include <cstddef>
#include <cassert>
#include <climits>

static size_t countFactorial(size_t operand)
{
  size_t factorial = 1;
  for (size_t i = 2; i <= operand; i++)
  {
    assert(factorial <= SIZE_MAX / i);
    factorial *= i;
  }
  return factorial;
}

FactorialContainer::const_iterator::const_iterator(size_t minOperand, size_t maxOperand, size_t operand, value_type value) :
  minOperand_(minOperand),
  maxOperand_(maxOperand),
  operand_(operand),
  value_(value)
{
  if (operand > maxOperand || operand < minOperand)
  {
    throw std::out_of_range("Factorial operand out of range");
  }
}

FactorialContainer::const_iterator::value_type FactorialContainer::const_iterator::operator*() const
{
  return value_;
}

FactorialContainer::const_iterator& FactorialContainer::const_iterator::operator++()
{
  if (operand_ == maxOperand_)
  {
    throw std::out_of_range("Factorial operand out of range in increment");
  }
  operand_++;
  value_ *= operand_;
  return *this;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator++(int)
{
  const_iterator temp = *this;
  ++(*this);
  return temp;
}

FactorialContainer::const_iterator& FactorialContainer::const_iterator::operator--()
{
  if (operand_ == minOperand_)
  {
    throw std::out_of_range("Factorial operand out of range in decrement");
  }
  value_ /= operand_;
  operand_--;
  return *this;
}

FactorialContainer::const_iterator FactorialContainer::const_iterator::operator--(int)
{
  const_iterator temp = *this;
  --(*this);
  return temp;
}

bool FactorialContainer::const_iterator::operator==(const const_iterator& it) const
{
  return (minOperand_ == it.minOperand_) 
      && (maxOperand_ == it.maxOperand_) 
      && (operand_ == it.operand_) 
      && (value_ == it.value_);
}

bool FactorialContainer::const_iterator::operator!=(const const_iterator& it) const
{
  return !(*this == it);
}

FactorialContainer::FactorialContainer() :
  size_(0),
  maxValue_(countFactorial(0))
{}

FactorialContainer::FactorialContainer(size_t operand) :
  size_(operand + 1),
  maxValue_(countFactorial(operand + 1))
{}

FactorialContainer::const_iterator FactorialContainer::begin() const
{
  return const_iterator(1, size_, 1, 1);
}

FactorialContainer::const_iterator FactorialContainer::end() const
{
  return const_iterator(1, size_, size_, maxValue_);
}

FactorialContainer::const_reverse_iterator FactorialContainer::rbegin() const
{
  return FactorialContainer::const_reverse_iterator(end());
}

FactorialContainer::const_reverse_iterator FactorialContainer::rend() const
{
  return FactorialContainer::const_reverse_iterator(begin());
}
