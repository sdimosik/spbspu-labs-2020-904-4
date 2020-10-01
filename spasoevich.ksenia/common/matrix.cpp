#include "matrix.hpp"

#include <iostream>
#include <stdexcept>
#include <cmath>

namespace spasoevich
{
  Matrix::Layer::Layer(shape_ptr* arr, size_t size) :
    size_(size),
    arr_(arr)
  {}

  Matrix::shape_ptr& Matrix::Layer::operator [](size_t index)
  {
    if (index >= size_ || size_==0)
    {
      throw std::out_of_range("Index is out of array");
    }

    return arr_[index];
  }

  Matrix::Matrix() :
    rows_(0),
    columns_(0),
    figures_(nullptr)
  {}

  Matrix::Matrix(const Matrix& other) :
    rows_(other.rows_),
    columns_(other.columns_),
    figures_(std::make_unique<shape_ptr[]>(other.rows_* other.columns_))
  {
    for (size_t i = 0; i < rows_ * columns_; i++)
    {
      figures_[i] = other.figures_[i];
    }
  }

  Matrix::Matrix(Matrix&& other) noexcept :
    rows_(other.rows_),
    columns_(other.columns_),
    figures_(std::move(other.figures_))
  {
    other.rows_ = 0;
    other.columns_ = 0;
    other.figures_.reset();
  }

  Matrix& Matrix::operator =(const Matrix& other)
  {
    if (this == &other)
    {
      return *this;
    }
    shape_array tempArray = std::make_unique<shape_ptr[]>(other.rows_ * other.columns_);
    for (size_t i = 0; i < other.rows_ * other.columns_; i++)
    {
      tempArray[i] = other.figures_[i];
    }
    rows_ = other.rows_;
    columns_ = other.columns_;
    figures_ = std::move(tempArray);
    return *this;
  }

  Matrix& Matrix::operator =(Matrix&& other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    rows_ = other.rows_;
    columns_ = other.columns_;
    figures_ = std::move(other.figures_);
    other.rows_ = 0;
    other.columns_ = 0;
    other.figures_.reset();
    return *this;
  }

  Matrix::Layer Matrix::operator [](const size_t index) const
  {
    if (index >= rows_ || rows_ == 0)
    {
      throw std::invalid_argument("Index is out of array");
    }
    return Layer(&figures_[columns_ * index], columns_);
  }

  void Matrix::addShape(const shape_ptr& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Matrix can't be empty");
    }

    size_t row = 1;
    for (size_t i = 0; i < rows_ * columns_; i++)
    {
      if (isOverlapping(figures_[i], shape))
      {
        row = (i / columns_) + 2;
      }
    }
    size_t tempRow = rows_;
    size_t tempColumn = columns_;
    size_t avaliableColumns = 0;

    if (row > rows_)
    {
      tempRow++;
      avaliableColumns = columns_;
    }
    else
    {
      for (size_t i = (row - 1) * columns_; i < row * columns_; i++)
      {
        if (figures_[i] == nullptr)
        {
          avaliableColumns++;
        }
      }
    }

    if (avaliableColumns == 0)
    {
      tempColumn++;
      avaliableColumns = 1;
    }

    if (tempRow != rows_ || tempColumn != columns_)
    {
      shape_array tempMatrixElem(std::make_unique<shape_ptr[]>(tempRow * tempColumn));

      for (size_t i = 0; i < tempRow; i++)
      {
        for (size_t j = 0; j < tempColumn; j++)
        {
          if (i >= rows_ || j >= columns_)
          {
            tempMatrixElem[i * tempColumn + j] = nullptr;
            continue;
          }
          tempMatrixElem[i * tempColumn + j] = figures_[i * columns_ + j];
        }
      }

      tempMatrixElem[row * tempColumn - avaliableColumns] = shape;

      figures_ = std::move(tempMatrixElem);
      rows_ = tempRow;
      columns_ = tempColumn;
    }
    else
    {
      figures_[row * tempColumn - avaliableColumns] = shape;
    }
  }

  bool Matrix::isOverlapping(const Matrix::shape_ptr& shape1, const Matrix::shape_ptr& shape2) const noexcept
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


  size_t Matrix::getRows() const
  {
    return rows_;
  }

  size_t Matrix::getColumns() const
  {
    return columns_;
  }

  void Matrix::printMatrixData() const
  {
    std::cout << "Number of rows: " << getRows() << "\n"
      << "Number of columns: " << getColumns() << "\n";
  }
}
