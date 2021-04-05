#ifndef COMP_SHAPE_HPP
#define COMP_SHAPE_HPP

#include <memory>
#include "shape.hpp"

namespace kharitonov 
{
  struct rectangle_t;
  struct point_t;
  class Matrix;

  class CompositeShape : public Shape 
  {
  public:
    CompositeShape();
    CompositeShape(const CompositeShape&);
    CompositeShape(CompositeShape&&) noexcept;
    ~CompositeShape() = default;

    CompositeShape& operator=(const CompositeShape&);
    CompositeShape& operator=(CompositeShape&&) noexcept;
    ShapePtr operator[](const size_t index) const;

    size_t getSize() const noexcept;
    point_t getCentre() const;
    double getArea() const override;
    rectangle_t getFrameRect() const override;
    Matrix getPartition() const;

    void move(point_t) override;
    void move(double, double) override;
    void scale(double) override;
    void rotate(double) override;

    void append(const ShapePtr&);
    void remove(const size_t index);

    void display() const override;
  private:
    size_t size_;
    ArrayShapePtr shapes_;
  };
}

#endif
