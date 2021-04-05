#include "composite-shape.hpp"

#define _USE_MATH_DEFINES
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <memory>

#include "matrix.hpp"
#include "shape.hpp"
#include "base-types.hpp"
#include "partitioning-logic.hpp"

kharitonov::CompositeShape::CompositeShape() :
  size_(0),
  shapes_(nullptr)
{}

kharitonov::CompositeShape::CompositeShape(const CompositeShape& inShape):
  size_(0),
  shapes_(nullptr)
{
  if (inShape.size_)
  {
    shapes_ = std::make_unique<ShapePtr[]>(inShape.size_);
    for (size_t s = 0; s < inShape.size_; s++)
    {
      shapes_[s] = inShape.shapes_[s];
    }
    size_ = inShape.size_;
  }
}

kharitonov::CompositeShape::CompositeShape(CompositeShape&& inShape) noexcept :
  size_(inShape.size_),
  shapes_(std::move(inShape.shapes_))
{
  inShape.size_ = 0;
}

kharitonov::CompositeShape& kharitonov::CompositeShape::operator=(const CompositeShape& inShape)
{
  if (this != &inShape)
  {
    if (inShape.size_)
    {
      shapes_ = std::make_unique<ShapePtr[]>(inShape.size_);
      for (size_t s = 0; s < size_; s++)
      {
        shapes_[s] = inShape.shapes_[s];
      }
      size_ = inShape.size_;
    }
    else
    {
      shapes_ = nullptr;
      size_ = 0;
    }
  }
  return *this;
}

kharitonov::CompositeShape& kharitonov::CompositeShape::operator=(CompositeShape&& inShape) noexcept
{
  size_ = inShape.size_;
  if (inShape.size_)
  {
    shapes_ = std::move(inShape.shapes_);
    inShape.size_ = 0;
  }
  return *this;
}

kharitonov::CompositeShape::ShapePtr kharitonov::CompositeShape::operator[](const size_t index) const
{
  if (index >= size_)
  {
    throw std::out_of_range("CompositeShape array index out of range");
  }
  return shapes_[index];
}

size_t kharitonov::CompositeShape::getSize() const noexcept
{
  return size_;
}

kharitonov::point_t kharitonov::CompositeShape::getCentre() const
{
  return getFrameRect().pos;
}

double kharitonov::CompositeShape::getArea() const
{
  double res = 0.0;
  for (size_t s = 0; s < size_; s++)
  {
    res += shapes_[s]->getArea();
  }
  return res;
}

kharitonov::Matrix kharitonov::CompositeShape::getPartition() const
{
  return kharitonov::partition(shapes_, size_);
}

kharitonov::rectangle_t kharitonov::CompositeShape::getFrameRect() const
{
  if (size_ <= 0) 
  {
    throw std::logic_error("CompositeShape array is empty");
  }
  rectangle_t figureRect = shapes_[0]->getFrameRect();
  double lastLeft = figureRect.pos.x - figureRect.width / 2;
  double lastRight = figureRect.pos.x + figureRect.width / 2;
  double lastTop = figureRect.pos.y + figureRect.height / 2;
  double lastBottom = figureRect.pos.y - figureRect.height / 2;
  for (size_t s = 1; s < size_; s++)
  {
    rectangle_t figureRect = shapes_[s]->getFrameRect();
    lastLeft = std::min(lastLeft, figureRect.pos.x - figureRect.width / 2);
    lastRight = std::max(lastRight, figureRect.pos.x + figureRect.width / 2);
    lastTop = std::max(lastTop, figureRect.pos.y + figureRect.height / 2);
    lastBottom = std::min(lastBottom, figureRect.pos.y - figureRect.height / 2);
  }
  return rectangle_t{ (lastRight - lastLeft), (lastTop - lastBottom), 
      {(lastRight - (lastRight - lastLeft) / 2),  (lastTop - (lastTop - lastBottom) / 2)}};
}

void kharitonov::CompositeShape::move(point_t newPos)
{
  move(newPos.x - getFrameRect().pos.x, newPos.y - getFrameRect().pos.y);
}

void kharitonov::CompositeShape::move(double deltaX, double deltaY)
{
  if (size_ <= 0)
  {
    throw std::logic_error("CompositeShape array is empty");
  }
  for (size_t s = 0; s < size_; s++)
  {
    shapes_[s]->move(deltaX, deltaY);
  }
}

void kharitonov::CompositeShape::scale(double factor)
{
  if (factor <= 0)
  {
    throw std::invalid_argument("Non-positive scaling factor");
  }
  if (size_ <= 0)
  {
    throw std::logic_error("CompositeShape array is empty");
  }
  const point_t centre = getCentre();
  for (size_t s = 0; s < size_; s++)
  {
    shapes_[s]->move({ centre.x + factor * (shapes_[s]->getFrameRect().pos.x - centre.x),
        centre.y + factor * (shapes_[s]->getFrameRect().pos.y - centre.y) });
    shapes_[s]->scale(factor);
  }
}

void kharitonov::CompositeShape::rotate(double angle)
{
  if (size_ <= 0)
  {
    throw std::logic_error("CompositeShape array is empty");
  }
  if (angle == 0)
  {
    return;
  }
  angle = std::fmod(angle, 180);
  if (angle <= 0)
  {
    angle += 180;
  }
  const double radAngle = angle * M_PI / 180;

  const point_t centre = getCentre();
  for (size_t s = 0; s < size_; s++)
  {
    point_t shapeCentre = shapes_[s]->getCentre();

    const double newX = centre.x + (shapeCentre.x - centre.x) * std::cos(radAngle) - (shapeCentre.y - centre.y) * std::sin(radAngle);
    const double newY = centre.y + (shapeCentre.x - centre.x) * std::sin(radAngle) + (shapeCentre.y - centre.y) * std::cos(radAngle);

    shapes_[s]->move({ newX, newY });
    shapes_[s]->rotate(angle);
  }
}

void kharitonov::CompositeShape::append(const ShapePtr& inShape)
{
  
  if (inShape == nullptr)
  {
    throw std::invalid_argument("Empty ShapePtr");
  }
  if (inShape.get() == this)
  {
    throw std::logic_error("Adding CompositeShape to itself");
  }
  ArrayShapePtr newShapes(new ShapePtr[size_ + 1]);
  for (size_t s = 0; s < size_; s++)
  {
    newShapes[s] = shapes_[s];
  }
  newShapes[size_] = inShape;
  size_++;
  shapes_ = std::move(newShapes);
}

void kharitonov::CompositeShape::remove(const size_t index)
{
  if (index >= size_)
  {
    throw std::out_of_range("CompositeShape array index out of range");
  }
  for (size_t s = index; s < size_-1; s++)
  {
    shapes_[s] = shapes_[s+1];
  }
  size_--;
  shapes_[size_].reset();
}

void kharitonov::CompositeShape::display() const
{
  std::cout << "CompositeShape contains " << size_ << " elements: \n";
  for (size_t s = 0; s < size_; s++)
  {
    shapes_[s]->display();
  }
}
