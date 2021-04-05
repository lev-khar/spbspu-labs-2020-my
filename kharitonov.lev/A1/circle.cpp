#include "circle.hpp"

Circle::Circle(const point_t &centre, double radius) :
  centre_(centre),
  radius_(radius)
{
  assert(radius > 0);
}

double Circle::getArea() const
{
  return M_PI * radius_ * radius_;
}

rectangle_t Circle::getFrameRect() const
{
  return rectangle_t{radius_ * 2, radius_ * 2, centre_};
}

void Circle::move(point_t newPoint)
{
  centre_ = newPoint;
}

void Circle::move(double deltaX, double deltaY)
{
  centre_.x += deltaX;
  centre_.y += deltaY;
}

void Circle::display() const
{
  std::cout << "There is a CIRCLE with a radius of " << radius_
            << "\nThe coordinates of the centre are ("
            << centre_.x << "; " << centre_.y << ").\n";
}
