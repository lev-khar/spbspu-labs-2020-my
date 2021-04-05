#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <memory>
#include "shape.hpp"

namespace kharitonov 
{
  class Matrix
  {
  public:
    class ConstLayer
    {
    public:
      const Shape::ShapePtr operator[](size_t) const;
      size_t getLength() const;
    protected: 
      size_t index_;
    private:
      const Matrix* matrix_;
      ConstLayer(const Matrix*, size_t);
      friend Matrix;
    };
    class Layer : public ConstLayer
    {
    public:
      void addShape(const Shape::ShapePtr&);
    private:
      Matrix* matrix_;
      Layer(Matrix*, size_t);
      friend Matrix;
    };

    Matrix();
    Matrix(const Matrix&);
    Matrix(Matrix&&) noexcept;
    ~Matrix() = default;
    Matrix& operator=(const Matrix&);
    Matrix& operator=(Matrix&&) noexcept;

    const ConstLayer operator[](const size_t) const;
    Layer operator[](size_t);
    size_t getLayersNumber() const;
    
    void addLayer();

    void display() const;
  private:
    size_t layersNumber_;
    size_t length_;
    Shape::ArrayShapePtr shapes_;
    void enlargeLength();
    void addToLayer(const Shape::ShapePtr&, size_t);
  };
}

#endif
