#include "matrix.hpp"
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace bakaeva
{
  Matrix::Matrix() :
    elements_(nullptr),
    rows_(0),
    columns_(0)
  {}

  Matrix::Matrix(const Matrix &other) :
    elements_(std::make_unique<shapePtr[]>(other.rows_ * other.columns_)),
    rows_(other.rows_),
    columns_(other.columns_)
  {
    for (size_t i = 0; i < rows_ * columns_; i++)
    {
      elements_[i] = other.elements_[i];
    }
  }

  Matrix::Matrix(Matrix &&other) noexcept :
    elements_(std::move(other.elements_)),
    rows_(other.rows_),
    columns_(other.columns_)
  {
    other.rows_ = 0;
    other.columns_ = 0;
    other.elements_.reset();
  }

  Matrix &Matrix::operator=(const Matrix &other)
  {
    if (this == &other)
    {
      return *this;
    }
    matrixElem temp = std::make_unique<shapePtr[]>(other.rows_ * other.columns_);
    for (size_t i = 0; i < other.rows_ * other.columns_; i++)
    {
      temp[i] = other.elements_[i];
    }
    rows_ = other.rows_;
    columns_ = other.columns_;
    elements_ = std::move(temp);
    return *this;
  }

  Matrix &Matrix::operator=(Matrix &&other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    rows_ = other.rows_;
    columns_ = other.columns_;
    elements_ = std::move(other.elements_);
    other.rows_ = 0;
    other.columns_ = 0;
    other.elements_.reset();
    return *this;
  }

  Matrix::Layer Matrix::operator[](const size_t index)
  {
    if (rows_ == 0 || index > rows_ - 1)
    {
      throw std::out_of_range(std::string("Index of row is out of range = ") += std::to_string(index));
    }
    return Layer(&elements_[columns_ * index], columns_);
  }

  void Matrix::addShape(const Matrix::shapePtr &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Added in matrix shape pointer must not be null!");
    }

    size_t shapeRow = 1;
    for (size_t i = 0; i < rows_ * columns_; i++)
    {
      if (isOverlapping(elements_[i], shape))
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

    if (tempRow != rows_ || tempColumn != columns_)
    {
      matrixElem tempMatrixElem(std::make_unique<shapePtr[]>(tempRow * tempColumn));

      for (size_t i = 0; i < tempRow; i++)
      {
        for (size_t j = 0; j < tempColumn; j++)
        {
          if (i >= rows_ || j >= columns_)
          {
            tempMatrixElem[i * tempColumn + j] = nullptr;
            continue;
          }
          tempMatrixElem[i * tempColumn + j] = elements_[i * columns_ + j];
        }
      }

      tempMatrixElem[shapeRow * tempColumn - freeColumns] = shape;

      elements_ = std::move(tempMatrixElem);
      rows_ = tempRow;
      columns_ = tempColumn;
    }
    else
    {
      elements_[shapeRow * tempColumn - freeColumns] = shape;
    }
  }

  size_t Matrix::getRows() const noexcept
  {
    return rows_;
  }

  size_t Matrix::getColumns() const noexcept
  {
    return columns_;
  }

  bool Matrix::isOverlapping(const Matrix::shapePtr &shape1, const Matrix::shapePtr &shape2) const noexcept
  {
    if (shape1 == nullptr || shape2 == nullptr)
    {
      return false;
    }
    rectangle_t frameRect1 = shape1->getFrameRect();
    rectangle_t frameRect2 = shape2->getFrameRect();
    return ((fabs(frameRect1.pos.x - frameRect2.pos.x) < ((frameRect1.width / 2) + (frameRect2.width / 2)))
            && (fabs(frameRect1.pos.y - frameRect2.pos.y) < ((frameRect1.height / 2) + (frameRect2.height / 2))));
  }

  void Matrix::printMatrix() const
  {
    std::cout << "Matrix size = " << rows_ * columns_ << '\n'
              << getRows() << " rows and " << getColumns() << " columns:\n";
    for (size_t i = 0; i < rows_; i++)
    {
      for (size_t j = 0; j < columns_; j++)
      {
        if (elements_[i * columns_ + j] != nullptr)
        {
          std::cout << i + 1 << '.' << j + 1 << '\n';
          elements_[i * columns_ + j]->printData();
        }
      }
    }
  }

  Matrix::Layer::Layer(shapePtr *shapes, size_t size) :
    shapes_(shapes),
    size_(size)
  {}

  Matrix::shapePtr &Matrix::Layer::operator[](size_t index)
  {
    if (index > size_ - 1 || size_ == 0)
    {
      throw std::out_of_range(std::string("Index of column is out of range = ") += std::to_string(index));
    }
    return shapes_[index];
  }
}
