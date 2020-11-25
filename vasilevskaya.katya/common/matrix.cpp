#include "matrix.hpp"
#include <iostream>
#include <memory>
#include "shape.hpp"
#include "composite-shape.hpp"
#include "base-types.hpp"

vasilevskaya::Matrix::Layer::Layer(const vasilevskaya::Matrix& matrix, size_t numberLayer):
  matrix_(matrix),
  numberLayer_(numberLayer)
{}

vasilevskaya::Shape::PointToShape& vasilevskaya::Matrix::Layer::operator[](size_t index) const
{
  if (index >= matrix_.line_)
  {
    throw std::out_of_range("Going beyond the boundaries of the layer array !\n");
  }
  return matrix_.arrayMatrix_[numberLayer_ * matrix_.line_ + index];
}

vasilevskaya::Matrix::Matrix():
  arrayMatrix_(nullptr),
  column_(0),
  line_(0)
{}

vasilevskaya::Matrix::Matrix(const Matrix& copiedMatrix):
  arrayMatrix_(std::make_unique<Shape::PointToShape[]>(copiedMatrix.getSizeMatrix())),
  column_(copiedMatrix.column_),
  line_(copiedMatrix.line_)
{
  for (size_t i = 0; i < copiedMatrix.getSizeMatrix(); i++)
  {
    arrayMatrix_[i] = copiedMatrix.arrayMatrix_[i];
  }
}

vasilevskaya::Matrix::Matrix(Matrix&& portableMatrix) noexcept:
  arrayMatrix_(std::move(portableMatrix.arrayMatrix_)),
  column_(portableMatrix.column_),
  line_(portableMatrix.line_)
{
  portableMatrix.column_ = 0;
  portableMatrix.line_ = 0;
}

vasilevskaya::Matrix& vasilevskaya::Matrix::operator=(const Matrix& copiedMatrix)
{
  if (this == &copiedMatrix)
  {
    return *this;
  }
  arrayMatrix_ = std::make_unique<Shape::PointToShape[]>(copiedMatrix.getSizeMatrix());
  for (size_t i = 0; i < copiedMatrix.getSizeMatrix(); i++)
  {
    arrayMatrix_[i] = copiedMatrix.arrayMatrix_[i];
  }
  column_ = copiedMatrix.column_;
  line_ = copiedMatrix.line_;
  return *this;
}

vasilevskaya::Matrix& vasilevskaya::Matrix::operator=(Matrix&& portableMatrix) noexcept
{
  if (this == &portableMatrix)
  {
    return *this;
  }
  arrayMatrix_ = std::move(portableMatrix.arrayMatrix_);
  column_ = portableMatrix.column_;
  portableMatrix.column_ = 0;
  line_ = portableMatrix.line_;
  portableMatrix.line_ = 0;
  return *this;
}

vasilevskaya::Matrix::Layer vasilevskaya::Matrix::operator[](size_t index) const
{
  if (index >= column_)
  {
    throw std::out_of_range("There was an out of bounds matrix !");
  }
  Layer layer(*this, index);
  return layer;
}

size_t vasilevskaya::Matrix::getSizeMatrix() const
{
  return line_ * column_;
}

size_t vasilevskaya::Matrix::getColumn() const
{
  return column_;
}

size_t vasilevskaya::Matrix::getLine() const
{
  return line_;
}

void vasilevskaya::Matrix::addShape(const Shape::PointToShape& newShape)
{
  if (!newShape)
  {
    throw std::invalid_argument("This cannot be added to the matrix !");
  }
  size_t layer = getNumberOfLayerForInsert(newShape);
  if (layer == column_)
  {
    extendMatrixInHeight();
  }
  size_t placeInLayer = findEmptyPlaceInLayer(layer);
  if (placeInLayer == line_)
  {
    extendMatrixInWidth();
  }
  arrayMatrix_[layer * line_ + placeInLayer] = newShape;
}

void vasilevskaya::Matrix::printMatrix() const
{
  for (size_t i = 0; i < column_; i++)
  {
    std::cout << "line :" << i + 1 << '\n';
    for (size_t j = 0; (arrayMatrix_[i * line_ + j] != nullptr) && (j < line_); j++)
    {
      arrayMatrix_[i * line_ + j]->printFigure();
    }
    std::cout << "\n\n";
  }
}

size_t vasilevskaya::Matrix::getNumberOfLayerForInsert(const Shape::PointToShape& newShape) const
{
  for (int i = column_ - 1; i >= 0; --i)
  {
    for (int j = line_ - 1; j >= 0; --j)
    {
      if (!arrayMatrix_[i * line_ + j])
      {
        continue;
      }
      if (isOverlap(arrayMatrix_[i * line_ + j]->getFrameRect(), newShape->getFrameRect()))
      {
        return i + 1;
      }
    }
  }
  return 0;
}

void vasilevskaya::Matrix::extendMatrixInWidth()
{
  std::unique_ptr<Shape::PointToShape[]> newArray = std::make_unique<Shape::PointToShape[]>(getSizeMatrix() + column_);
  size_t lineForNewArray = line_ + 1;
  size_t index = 0;
  for (size_t i = 0; i < column_; i++)
  {
    for (size_t j = 0; j < line_; j++)
    {
      newArray[i * lineForNewArray + j] = arrayMatrix_[index];
      index++;
    }
  }
  line_ = lineForNewArray;
  arrayMatrix_.swap(newArray);
}

void vasilevskaya::Matrix::extendMatrixInHeight()
{
  size_t initialSizeMatrix = getSizeMatrix();
  std::unique_ptr<Shape::PointToShape[]> newArray = std::make_unique<Shape::PointToShape[]>(initialSizeMatrix + line_);
  for (size_t i = 0; i < initialSizeMatrix; i++)
  {
    newArray[i] = arrayMatrix_[i];
  }
  column_++;
  arrayMatrix_.swap(newArray);
}

size_t vasilevskaya::Matrix::findEmptyPlaceInLayer(size_t layer) const
{
  size_t leftBorder = layer * line_;
  size_t rightBorder = leftBorder + line_;
  for (size_t i = leftBorder; i < rightBorder; i++)
  {
    if (!arrayMatrix_[i])
    {
      return i - leftBorder;
    }
  }
  return line_;
}
