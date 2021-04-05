#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"

class Rectangle: public Shape
{
public:
  explicit Rectangle(const rectangle_t &rect);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t) override;
  void move(double, double) override;
  void display() const override;

private:
  rectangle_t rect_;
};

#endif
