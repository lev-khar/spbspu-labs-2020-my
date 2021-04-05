#ifndef PARTITIONING_HPP
#define PARTITIONING_HPP
#include "shape.hpp"

namespace kharitonov {
  class Matrix;

  Matrix partition(const Shape::ArrayShapePtr&, size_t);
}

#endif
