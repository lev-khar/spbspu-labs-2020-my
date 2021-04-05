#ifndef SHAPE_HPP
#define SHAPE_HPP
#include <memory>

namespace kharitonov {
  struct rectangle_t;
  struct point_t;

  class Shape{ 
  public:
    using ShapePtr  = std::shared_ptr<Shape>;
    using ArrayShapePtr = std::unique_ptr<Shape::ShapePtr[]>;

    virtual ~Shape() = default;

    virtual double getArea() const = 0;
    virtual rectangle_t getFrameRect() const = 0;
    virtual point_t getCentre() const = 0;

    virtual void move(point_t) = 0;
    virtual void move(double, double) = 0;
    virtual void scale(double) = 0;
    virtual void rotate(double) = 0;

    virtual void display() const = 0;
  };
}

#endif
