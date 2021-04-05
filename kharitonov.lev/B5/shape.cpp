#include "shape.hpp"
#include <iostream>
#include <utility>
#include <algorithm>
#include <iterator>
#include <cmath>
#include "readutils.hpp"

double countDistance(const Point& p1, const Point& p2)
{
  return std::sqrt(std::pow((p1.x - p2.x), 2) + std::pow((p1.y - p2.y), 2));
}

bool isRectangle(const Shape& shape)
{
  if (shape.size() != RECTANGLE_VERTICES)
  {
    return false;
  }
  const double s1 = countDistance(shape[0], shape[1]);
  const double s2 = countDistance(shape[1], shape[2]);
  const double s3 = countDistance(shape[2], shape[3]);
  const double s4 = countDistance(shape[3], shape[0]);
  const double dia1 = countDistance(shape[0], shape[2]);
  const double dia2 = countDistance(shape[1], shape[3]);
  return (s1 == s3) && (s2 == s4) && (dia1 == dia2);
}

bool isSquare(const Shape& shape)
{
  if (!isRectangle(shape))
  {
    return false;
  }
  const double s1 = countDistance(shape[0], shape[1]);
  const double s2 = countDistance(shape[1], shape[2]);
  return (s1 == s2);
}

ShapeType getType(const Shape& shape)
{
  if (shape.size() == TRIANGLE_VERTICES)
  {
    return TRIANGLE;
  }
  if (isSquare(shape))
  {
    return SQUARE;
  }
  if (isRectangle(shape))
  {
    return RECTANGLE;
  }
  if (shape.size() == PENTAGON_VERTICES)
  {
    return PENTAGON;
  }
  else
  {
    return OTHER;
  }
}

std::istream& operator>>(std::istream& in, Point& point)
{
  StreamGuard guard(in);
  in >> std::noskipws;

  char mark;
  if (!(in >> skipWs >> mark))
  {
    return in;
  }
  if (mark != '(')
  {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }

  if (!(in >> skipWs >> point.x))
  {
    return in;
  }

  if (!(in >> skipWs >> mark))
  {
    return in;
  }
  if (mark != ';')
  {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }

  if (!(in >> skipWs >> point.y))
  {
    return in;
  }

  if (!(in >> skipWs >> mark))
  {
    return in;
  }
  if (mark != ')')
  {
    in.unget();
    in.setstate(std::ios::failbit);
    return in;
  }
  return in;
}

std::ostream& operator<<(std::ostream& out, const Point& point)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << '(' << point.x << ";" << point.y << ")";
  }
  return out;
}

std::istream& operator>>(std::istream& in, Shape& shape)
{
  StreamGuard guard(in);
  in >> std::noskipws;
  in >> std::ws;

  int count;
  if (!(in >> count))
  {
    return in;
  }
  Shape temp;
  while (count > 0)
  {
    Point point;
    if (!(in >> skipWs >> point))
    {
      return in;
    }
    temp.push_back(point);
    count--;
  }
  if ((in >> skipWs).peek() == '\n' || in.eof())
  {
    shape = std::move(temp);
    auto state = in.rdstate();
    state &= ~std::ios_base::failbit;
    in.clear(state);
  }
  else
  {
    in.setstate(std::ios::failbit);
  }

  return in;
}

std::ostream& operator<<(std::ostream& out, const Shape& shape)
{
  std::ostream::sentry sentry(out);
  if (sentry)
  {
    out << shape.size() << ' ';
    std::copy(shape.begin(), shape.end(), std::ostream_iterator<Point>(out, " "));
  }
  return out;
}
