#include "matrix.hpp"

#include <iostream>

ushakov::Matrix::Layer::Layer(std::shared_ptr<Shape> *shapes, size_t size) :
  shapes_(shapes),
  size_(size)
{}

std::shared_ptr<ushakov::Shape>& ushakov::Matrix::Layer::operator[](size_t index)
{
  if (index > size_ - 1 || size_ == 0)
  {
    throw std::out_of_range("Layer operator[] error: Index of column is out of range("
          + std::to_string(index) + ')');
  }

  return shapes_[index];
}

ushakov::Matrix::Matrix() :
  elements_(nullptr),
  rows_(0),
  columns_(0)
{}

ushakov::Matrix::Matrix(const Matrix& matrix) :
  elements_(std::make_unique<std::shared_ptr<Shape>[]>(matrix.rows_ * matrix.columns_)),
  rows_(matrix.rows_),
  columns_(matrix.columns_)
{
  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    elements_[i] = matrix.elements_[i];
  }
}

ushakov::Matrix::Matrix(Matrix&& matrix) noexcept:
  elements_(std::move(matrix.elements_)),
  rows_(matrix.rows_),
  columns_(matrix.columns_)
{
  matrix.rows_ = 0;
  matrix.columns_ = 0;
  matrix.elements_.reset();
}

ushakov::Matrix& ushakov::Matrix::operator=(const Matrix& matrix)
{
  if (this == &matrix)
  {
    return *this;
  }

  elements_ = std::make_unique<std::shared_ptr<Shape>[]>(matrix.rows_ * matrix.columns_);

  for (size_t i = 0; i < matrix.rows_ * matrix.columns_; i++)
  {
    elements_[i] = matrix.elements_[i];
  }

  rows_ = matrix.rows_;
  columns_ = matrix.columns_;

  return *this;
}

ushakov::Matrix& ushakov::Matrix::operator=(Matrix&& matrix) noexcept
{
  if (this == &matrix)
  {
    return *this;
  }

  rows_ = matrix.rows_;
  columns_ = matrix.columns_;
  elements_ = std::move(matrix.elements_);

  matrix.rows_ = 0;
  matrix.columns_ = 0;
  matrix.elements_.reset();

  return *this;
}

ushakov::Matrix::Layer ushakov::Matrix::operator[](size_t index)
{
  if (rows_ == 0 || index > rows_ - 1)
  {
    throw std::out_of_range("Matrix operator[] error: Index of row is out of range(" + std::to_string(index) + ')');
  }

  if (!elements_[columns_ * index])
  {
    throw std::invalid_argument("Matrix operator[] error: null pointer to shape at index " + std::to_string(columns_ * index));
  }

  return {&elements_[columns_ * index], columns_};
}

void ushakov::Matrix::addShape(const std::shared_ptr<Shape>& shape)
{
  if (shape == nullptr)
  {
    throw std::invalid_argument("Matrix addShape error: Invalid shape");
  }

  if (shape->getFrameRect().width == 0 || shape->getFrameRect().height == 0)
  {
    throw std::invalid_argument("CompositeShape addShape error: Empty shape");
  }

  size_t shapeRow = 1;

  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    if (!elements_[i])
    {
      continue;
    }

    if (isIntersecting(elements_[i], shape))
    {
      shapeRow = i / columns_ + 2;
    }
  }

  size_t tempRow = rows_;
  size_t tempColumn = columns_;
  size_t freeColumns = 0;

  if (shapeRow > rows_)
  {
    tempRow++;
    freeColumns = columns_;
  }
  else
  {
    for (size_t i = (shapeRow - 1) * columns_; i < shapeRow * columns_; i++)
    {
      if (!elements_[i])
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

  if (tempRow != rows_ || tempColumn != columns_)
  {
    matrixElement tempMatrixElements(std::make_unique<std::shared_ptr<Shape>[]>(tempRow * tempColumn));

    for (size_t i = 0; i < tempRow; i++)
    {
      for (size_t j = 0; j < tempColumn; j++)
      {
        if (i >= rows_ || j >= columns_)
        {
          tempMatrixElements[i * tempColumn + j] = nullptr;
          continue;
        }

        tempMatrixElements[i * tempColumn + j] = elements_[i * columns_ + j];
      }
    }

    tempMatrixElements[shapeRow * tempColumn - freeColumns] = shape;

    elements_ = std::move(tempMatrixElements);
    rows_ = tempRow;
    columns_ = tempColumn;
  }
  else
  {
    elements_[shapeRow * tempColumn - freeColumns] = shape;
  }
}

size_t ushakov::Matrix::getRows() const noexcept
{
  return rows_;
}

size_t ushakov::Matrix::getColumns() const noexcept
{
  return columns_;
}

void ushakov::Matrix::print() const noexcept
{
  std::cout << "Matrix size = " << rows_ * columns_ << std::endl;
  std::cout << getRows() << " rows and " << getColumns() << " columns:" << std::endl;

  for (size_t i = 0; i < rows_; i++)
  {

    for (size_t j = 0; j < columns_; j++)
    {
      if (elements_[i * columns_ + j] != nullptr)
      {
        std::cout << std::endl;
        std::cout << "row " << i + 1 << " column " << j + 1 << ": ";

        elements_[i * columns_ + j]->print();
      }
    }
  }
}

bool
ushakov::Matrix::isIntersecting(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2) noexcept
{
  if (shape1 == nullptr || shape2 == nullptr)
  {
    return false;
  }

  const rectangle_t rectangle1 = shape1->getFrameRect();
  const rectangle_t rectangle2 = shape2->getFrameRect();

  return ((std::abs(rectangle1.pos.x - rectangle2.pos.x) < ((rectangle1.width / 2) + (rectangle2.width / 2)))
        && (std::abs(rectangle1.pos.y - rectangle2.pos.y) < ((rectangle1.height / 2) + (rectangle2.height / 2))));
}
