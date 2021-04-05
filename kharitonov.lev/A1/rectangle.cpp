#include "rectangle.hpp"

Rectangle::Rectangle(const rectangle_t &rect):
  rect_(rect)
{
  assert((rect.width > 0) && (rect.height > 0));
}

double Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

rectangle_t Rectangle::getFrameRect() const
{
  return rect_;
}

void Rectangle::move(point_t newPoint)
{
  rect_.pos = newPoint;
}

void Rectangle::move(double deltaX, double deltaY)
{
  rect_.pos.x += deltaX;
  rect_.pos.y += deltaY;
}

void Rectangle::display() const
{
  std::cout << "There is a RECTANGLE with a height of " << rect_.height
            << " and a width of " << rect_.width
            << "\nThe coordinates of the centre are ("
            << rect_.pos.x << "; " << rect_.pos.y << ").\n";
}

