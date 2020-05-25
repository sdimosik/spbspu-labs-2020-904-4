//
// Created by sdimosik on 24.05.2020.
//

#include <iostream>
#include "matrix.hpp"

shabinsky::Matrix::Matrix() :
  elements_(nullptr),
  rows_(0),
  columns_(0)
{}

shabinsky::Matrix::Matrix(const shabinsky::Matrix &matrix) :
  elements_(std::make_unique<shapePtr[]>(getSize())),
  rows_(matrix.rows_),
  columns_(matrix.columns_)
{
  for (size_t i = 0; i < getSize(); i++)
  {
    elements_[i] = matrix.elements_[i];
  }
}

shabinsky::Matrix::Matrix(shabinsky::Matrix &&matrix) noexcept:
  elements_(std::move(matrix.elements_)),
  rows_(matrix.rows_),
  columns_(matrix.columns_)
{
  matrix.rows_ = 0;
  matrix.columns_ = 0;
  matrix.elements_.reset();
}

void shabinsky::Matrix::add(const shabinsky::Matrix::shapePtr &shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Shape pointer is null");
  }
  
  size_t layer = 1;
  for (size_t i = 0; i < getSize(); i++)
  {
    if (isOverlay(elements_[i], shape))
    {
      layer = i / columns_ + 2;
    }
  }
  
  size_t tempRow = rows_;
  size_t tempColumn = columns_;
  size_t freeColumns = 0;
  
  if (layer > rows_)
  {
    tempRow++;
    freeColumns = columns_;
  }
  else
  {
    //row = layer
    for (size_t i = columns_ * (layer - 1); i < layer * columns_; i++)
    {
      if (elements_[i] == nullptr)
      {
        freeColumns++;
      }
    }
  }
  
  if (freeColumns == 0)
  {
    tempColumn++;
    freeColumns = 1;
  }
  
  matrixPtr tempElements(std::make_unique<shapePtr[]>(tempRow * tempColumn));
  
  for (size_t i = 0; i < tempRow; i++)
  {
    for (size_t j = 0; j < tempColumn; j++)
    {
      if (i >= rows_ || j >= columns_)
      {
        tempElements[i * tempColumn + j] = nullptr;
        continue;
      }
      tempElements[i * tempColumn + j] = elements_[i * columns_ + j];
    }
  }
  
  tempElements[layer * tempColumn - freeColumns] = shape;
  
  elements_ = std::move(tempElements);
  rows_ = tempRow;
  columns_ = tempColumn;
}

bool
shabinsky::Matrix::isOverlay(const shabinsky::Matrix::shapePtr &shape1, const shabinsky::Matrix::shapePtr &shape2)
{
  rectangle_t rectangle1 = shape1->getFrameRect();
  rectangle_t rectangle2 = shape2->getFrameRect();
  double
    x11 = rectangle1.pos.x - rectangle1.width / 2,
    x12 = rectangle1.pos.x + rectangle1.width / 2,
    x21 = rectangle2.pos.x - rectangle2.width / 2,
    x22 = rectangle2.pos.x + rectangle2.width / 2,
    y11 = rectangle1.pos.y + rectangle1.height / 2,
    y12 = rectangle1.pos.y - rectangle1.height / 2,
    y21 = rectangle2.pos.y + rectangle2.height / 2,
    y22 = rectangle2.pos.y - rectangle2.height / 2;
  
  return x11 >= x21 &&
         x12 <= x22 &&
         y11 <= y21 &&
         y12 >= y22;
}

void shabinsky::Matrix::remove(size_t layerNumber, size_t shapeNumberInLayer)
{
  if (layerNumber >= rows_ || shapeNumberInLayer >= columns_ || rows_ * columns_ == 0)
  {
    throw std::out_of_range(std::string("Data is out of range. Your data = Rows:  ")
                            + std::to_string(layerNumber) + std::string(" Columns: ")
                            + std::to_string(shapeNumberInLayer));
  }
  
  elements_[layerNumber * columns_ + shapeNumberInLayer] = nullptr;
}

void shabinsky::Matrix::print() const
{
  std::cout << "Matrix\n";
  for (size_t i = 0; i < rows_; i++)
  {
    for (size_t j = 0; j < columns_; j++)
    {
      if (elements_[i * columns_ + j] != nullptr)
      {
        std::cout << "Layer: " << i << " Num:" << j << '\n';
        elements_[i * columns_ + j]->show(std::cout);
        std::cout << '\n';
      }
    }
  }
}

size_t shabinsky::Matrix::getRows() const
{
  return rows_;
}

size_t shabinsky::Matrix::getColumns() const
{
  return columns_;
}

size_t shabinsky::Matrix::getSize() const
{
  return rows_ * columns_;
}

shabinsky::Matrix::matrixPtr::pointer shabinsky::Matrix::operator[](size_t index) const
{
  if (rows_ == 0 || index > rows_)
  {
    throw std::out_of_range(std::string("Index is out of range = ") + std::to_string(index));
  }
  return elements_.get() + index * columns_;
}
