#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include "shape.hpp"
#include "base-types.hpp"

namespace kharitonov {
  class Rectangle : public Shape {
  public:
    Rectangle(const rectangle_t &, double angle = 0);

    double getHeight() const;
    double getWidth() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    point_t getCentre() const;

    void move(point_t) override;
    void move(double, double) override;
    void scale(double) override;
    void rotate(double) override;

    void display() const override;
  private:
    rectangle_t rect_;

    /*An angle between the positive direction of the horzontal axis in orthogonal coordinate system
      and a line that is perpendicular to the sides ot the rectangle that are equal to rect_.height 
      and passes through its centre. 0 by default.
      180° >= angle_ >= 0° */
    double angle_; 
  };
}

#endif
