#ifndef CIRCLE_HPP
#define CIRCLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace kharitonov {
  class Circle : public Shape {
  public:
    Circle(const point_t &, double, double angle = 0);

    double getRadius() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    point_t getCentre() const;

    void move(point_t) override;
    void move(double, double) override;
    void scale(double) override;
    void rotate(double) override;

    void display() const override;
  private:
    point_t centre_;
    double radius_;
    double angle_;
  };
}

#endif
