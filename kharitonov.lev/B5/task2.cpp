#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <stdexcept>
#include <vector>
#include "shape.hpp"

void task2(std::istream& in, std::ostream& out)
{
  std::istream_iterator<Shape> inputIterator(in);
  std::istream_iterator<Shape> endIterator;
  std::vector<Shape> shapes(inputIterator, endIterator);

  if (!in.eof()) 
  {
    throw std::runtime_error("Input error");
  }
  out << "Vertices: " << std::accumulate(shapes.begin(), shapes.end(), 0,
      [](size_t sum, const Shape& shape) { return sum + shape.size(); });

  out << "\nTriangles: " << std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return getType(shape) == ShapeType::TRIANGLE; });

  out << "\nSquares: " << std::count_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return getType(shape) == ShapeType::SQUARE; });

  out << "\nRectangles: " << std::count_if(shapes.begin(), shapes.end(),
    [](const Shape& shape) { return (getType(shape) == ShapeType::RECTANGLE) || (getType(shape) == ShapeType::SQUARE); });

  shapes.erase(std::remove_if(shapes.begin(), shapes.end(),
      [](const Shape& shape) { return getType(shape) == PENTAGON; }), shapes.end());

  std::vector<Point> points(shapes.size());
  std::transform(shapes.begin(), shapes.end(), points.begin(),
      [](const Shape& shape) { return shape[0]; });
  out << "\nPoints: ";
  std::copy(points.begin(), points.end(), std::ostream_iterator<Point>(out, " "));

  std::sort(shapes.begin(), shapes.end(), 
      [](const Shape& shape1, const Shape& shape2)
      { return getType(shape1) < getType(shape2); });
  out << "\nShapes:\n";
  std::copy(shapes.begin(), shapes.end(), std::ostream_iterator<Shape>(out, "\n"));
}
