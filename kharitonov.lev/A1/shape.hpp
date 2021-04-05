#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <cmath>
#include <cassert>
#include <iostream>
#include "base-types.hpp"

class Shape
{
public:
  virtual ~Shape() = default;
  virtual double getArea() const = 0;
  virtual rectangle_t getFrameRect() const = 0;
  virtual void move(point_t) = 0;
  virtual void move(double, double) = 0;
  virtual void display() const = 0;
};

#endif
