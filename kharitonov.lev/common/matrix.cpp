#include <memory>
#include <stdexcept>
#include <iostream>
#include "matrix.hpp"
#include "shape.hpp"

kharitonov::Matrix::Matrix() :
  layersNumber_(0),
  length_(0),
  shapes_(nullptr)
{
}

kharitonov::Matrix::Matrix(const Matrix& inMatrix) :
  layersNumber_(inMatrix.layersNumber_),
  length_(inMatrix.length_),
  shapes_(nullptr)
{
  if (inMatrix.layersNumber_)
  {
    shapes_ = std::make_unique<Shape::ShapePtr[]>(inMatrix.layersNumber_ * inMatrix.length_);
    for (size_t s = 0; s < inMatrix.layersNumber_ * inMatrix.length_; s++)
    {
      shapes_[s] = inMatrix.shapes_[s];
    }
  }
}

kharitonov::Matrix::Matrix(Matrix&& inMatrix) noexcept :
  layersNumber_(inMatrix.layersNumber_),
  length_(inMatrix.length_),
  shapes_(std::move(inMatrix.shapes_))
{
  inMatrix.layersNumber_ = 0;
  inMatrix.length_ = 0;
}

kharitonov::Matrix& kharitonov::Matrix::operator=(const Matrix& inMatrix)
{
  if (this != &inMatrix)
  {
    if (inMatrix.layersNumber_)
    {
      shapes_ = std::make_unique<Shape::ShapePtr[]>(inMatrix.layersNumber_ * inMatrix.length_);
      for (size_t s = 0; s < inMatrix.layersNumber_ * inMatrix.length_; s++)
      {
        shapes_[s] = inMatrix.shapes_[s];
      }
      layersNumber_ = inMatrix.layersNumber_;
      length_ = inMatrix.length_;
    }
    else
    {
      layersNumber_ = 0;
      length_ = 0;
      shapes_ = nullptr;
    }
  }
  return *this;
}

kharitonov::Matrix& kharitonov::Matrix::operator=(Matrix&& inMatrix) noexcept
{
  layersNumber_ = inMatrix.layersNumber_;
  length_ = inMatrix.length_;
  shapes_ = std::move(inMatrix.shapes_);
  inMatrix.layersNumber_ = 0;
  inMatrix.length_ = 0;
  return *this;
}

const kharitonov::Matrix::ConstLayer kharitonov::Matrix::operator[](size_t index) const
{
  if (index >= layersNumber_)
  {
    throw std::out_of_range("Matrix layer index out of range");
  }
  return ConstLayer(this, index);
}

kharitonov::Matrix::Layer kharitonov::Matrix::operator[](size_t index)
{
  if (index >= layersNumber_)
  {
    throw std::out_of_range("Matrix layer index out of range");
  }
  return Layer(this, index);
}

size_t kharitonov::Matrix::getLayersNumber() const
{
  return layersNumber_;
}

void kharitonov::Matrix::addLayer()
{
  Shape::ArrayShapePtr newShapes(new Shape::ShapePtr[length_ * (layersNumber_ + 1)]);
  for (size_t s = 0; s < length_ * layersNumber_; s++)
  {
    newShapes[s] = shapes_[s];
  }
  shapes_ = std::move(newShapes);
  layersNumber_++;
}

void kharitonov::Matrix::enlargeLength()
{
  size_t i = 0;
  Shape::ArrayShapePtr newShapes(new Shape::ShapePtr[(length_ + 1) * layersNumber_]);
  for (size_t s = 0; s < layersNumber_; s++)
  {
    for (size_t p = s * (length_ + 1); p < (s + 1) * (length_ + 1); p++)
    {
      if ((p != length_) && (i < length_ * layersNumber_))
      {
        newShapes[p] = shapes_[i];
        i++;
      }
    }
  }
  shapes_ = std::move(newShapes);
  length_++;
}

void kharitonov::Matrix::display() const
{
  for (size_t s = 0; s < layersNumber_; s++)
  {
    std::cout << "\n\nLayer " << s << ": \n\n";
    for (size_t p = s * length_; p < (s + 1) * length_; p++)
    {
      if (shapes_[p])
      {
        shapes_[p]->display();
      }
      else
      {
        std::cout << "*\n";
      }
    }
  }
}

void kharitonov::Matrix::addToLayer(const Shape::ShapePtr& inShape, size_t layerIndex)
{
  if (inShape == nullptr)
  {
    throw std::invalid_argument("Empty ShapePtr");
  }
  if (layerIndex > layersNumber_)
  {
    throw std::out_of_range("Matrix index out of range");
  }
  size_t s;
  for (s = 0; s < length_; s++)
  {
    if (shapes_[length_ * layerIndex + s] == nullptr)
    {
      break;
    }
  }
  if (s == length_)
  {
    enlargeLength();
  }
  shapes_[length_ * layerIndex + s] = inShape;
}

kharitonov::Matrix::ConstLayer::ConstLayer(const Matrix* matrix, size_t index) :
  index_(index),
  matrix_(matrix)
{
}

const kharitonov::Shape::ShapePtr kharitonov::Matrix::ConstLayer::operator[](size_t elmntIndex) const
{
  if (elmntIndex >= this->getLength())
  {
    throw std::out_of_range("Layer element index out of range");
  }
  return matrix_->shapes_[matrix_->length_ * index_ + elmntIndex];
}

size_t kharitonov::Matrix::ConstLayer::getLength() const
{
  size_t s;
  for (s = 0; s < matrix_->length_; s++)
  {
    if (matrix_->shapes_[index_ * matrix_->length_ + s] == nullptr)
    {
      return s;
    }
  }
  return matrix_->length_;
}

kharitonov::Matrix::Layer::Layer(Matrix* matrix, size_t index) :
  ConstLayer(matrix, index),
  matrix_(matrix)
{
}

void kharitonov::Matrix::Layer::addShape(const Shape::ShapePtr& inShape)
{
  matrix_->addToLayer(inShape, index_);
}
