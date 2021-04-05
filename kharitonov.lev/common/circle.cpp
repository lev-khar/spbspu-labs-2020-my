#include "circle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"

kharitonov::Circle::Circle(const point_t &centre, double radius, double angle) :
  centre_(centre),
  radius_(radius),
  angle_(angle)
  {
    if (radius <= 0)
    {
      throw std::invalid_argument("Non-positive radius of a circle");
    }
}

double kharitonov::Circle::getRadius() const
{
  return radius_;
}

double kharitonov::Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

kharitonov::rectangle_t kharitonov::Circle::getFrameRect() const
{
  return rectangle_t{radius_ * 2, radius_ * 2, centre_};
}

kharitonov::point_t kharitonov::Circle::getCentre() const
{
  return centre_;
}

void kharitonov::Circle::move(point_t newPoint)
{
  centre_ = newPoint;
}

void kharitonov::Circle::move(double deltaX, double deltaY)
{
  centre_.x += deltaX;
  centre_.y += deltaY;
}

void kharitonov::Circle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Non-positive scaling factor");
  }
  radius_ *= factor;
}

void kharitonov::Circle::rotate(double angle)
{
  angle_ = angle;
}

void kharitonov::Circle::display() const
{
  std::cout << "There is a CIRCLE with a radius of " << radius_
            << "\nThe coordinates of the centre are ("
            << centre_.x << "; " << centre_.y << ").\n";
}
