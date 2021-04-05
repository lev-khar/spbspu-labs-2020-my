#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"

class Circle: public Shape
{
public:
  Circle(const point_t &, double);
  double getArea() const override;
  rectangle_t getFrameRect() const override;
  void move(point_t newPoint) override;
  void move(double, double) override;
  void display() const override;
private:
  point_t centre_;
  double radius_;
};

#endif
