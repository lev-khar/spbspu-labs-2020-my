#include "rectangle.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include "base-types.hpp"

kharitonov::Rectangle::Rectangle(const rectangle_t &rect, double angle):
  rect_(rect),
  angle_(angle)
{
  if ((rect.height <= 0) || (rect.width <= 0))
  {
    throw std::invalid_argument("Non-positive parameters of a rectangle");
  }
}

double kharitonov::Rectangle::getHeight() const
{
  return rect_.height;
}

double kharitonov::Rectangle::getWidth() const
{
  return rect_.width;
}

double kharitonov::Rectangle::getArea() const
{
  return rect_.width * rect_.height;
}

kharitonov::rectangle_t kharitonov::Rectangle::getFrameRect() const
{
  if (angle_ != 0)
  {
    double radAngle = 0, newHeight, newWidth;
    if (angle_ == 90)
    {
      return {rect_.height, rect_.width, rect_.pos};
    }
    else if (angle_ < 90)
    {
      radAngle = angle_ * M_PI / 180;
    }
    else if (angle_ > 90)
    {
      radAngle = (angle_ - 90) * M_PI / 180;
    }
    newHeight = rect_.width * std::sin(radAngle) + rect_.height * std::cos(radAngle);
    newWidth = rect_.height * std::sin(radAngle) + rect_.width * std::cos(radAngle);
    return { newWidth, newHeight, rect_.pos };
  }
  return rect_;
}

kharitonov::point_t kharitonov::Rectangle::getCentre() const
{
  return rect_.pos;
}

void kharitonov::Rectangle::move(point_t newPoint)
{
  rect_.pos = newPoint;
}

void kharitonov::Rectangle::move(double deltaX, double deltaY)
{
  rect_.pos.x += deltaX;
  rect_.pos.y += deltaY;
}

void kharitonov::Rectangle::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Non-positive scaling factor");
  }
  rect_.height *= factor;
  rect_.width *= factor;
}

void kharitonov::Rectangle::rotate(double angle)
{
  angle_ += angle;
  angle_ = std::fmod(angle_,180);
  if (angle_ <= 0)
  {
    angle_ += 180;
  }
}

void kharitonov::Rectangle::display() const
{
  std::cout << "There is a RECTANGLE with a height of " << rect_.height
            << " and a width of " << rect_.width
            << "\nThe coordinates of the centre are ("
            << rect_.pos.x << "; " << rect_.pos.y << ").\n";
}

