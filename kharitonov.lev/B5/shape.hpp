#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <iostream>
#include <vector>

struct Point
{
  int x, y;
};

enum ShapeType
{
  TRIANGLE,
  SQUARE,
  RECTANGLE,
  PENTAGON,
  OTHER
};

const size_t TRIANGLE_VERTICES = 3;
const size_t RECTANGLE_VERTICES = 4;
const size_t PENTAGON_VERTICES = 5;

using Shape = std::vector<Point>;

ShapeType getType(const Shape&);
std::istream& operator>>(std::istream&, Point&);
std::ostream& operator<<(std::ostream&, const Point&);

std::istream& operator>>(std::istream&, Shape&);
std::ostream& operator<<(std::ostream&, const Shape&);

#endif
