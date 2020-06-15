#include "matrix.hpp"
#include <stdexcept>
#include <string>

namespace biryukova
{
  Matrix::Matrix() :
    rows_(0),
    columns_(0),
    shapes_(nullptr)
  {}

  Matrix::Matrix(const Matrix& m) :
    rows_(m.rows_),
    columns_(m.columns_),
    shapes_(std::make_unique<shapePtr[]>(m.rows_* m.columns_))
  {
    for (size_t i = 0; i < (rows_ * columns_); i++)
    {
      shapes_[i] = m.shapes_[i];
    }
  }

  Matrix::Matrix(Matrix&& m) noexcept :
    rows_(m.rows_),
    columns_(m.columns_),
    shapes_(std::move(m.shapes_))
  {
    m.rows_ = 0;
    m.columns_ = 0;
  }

  Matrix& Matrix::operator=(const Matrix& m)
  {
    if (this != &m)
    {
      shapes_.reset(new shapePtr[m.rows_ * m.columns_]);
      rows_ = m.rows_;
      columns_ = m.columns_;
      for (size_t i = 0; i < (rows_ * columns_); i++)
      {
        shapes_[i] = m.shapes_[i];
      }
    }
    return *this;
  }

  Matrix& Matrix::operator=(Matrix&& m) noexcept
  {
    if (this != &m)
    {
      rows_ = m.rows_;
      columns_ = m.columns_;
      shapes_ = std::move(m.shapes_);
      m.rows_ = 0;
      m.columns_ = 0;
    }
    return *this;
  }

  Matrix::Layer Matrix::operator[](size_t index) const
  {
    if (index > rows_ - 1 || rows_ == 0)
    {
      throw std::out_of_range("Index is invalid. Invalid index: "
        + std::to_string(index));
    }
    return Layer(&shapes_[columns_ * index], columns_);
  }

  size_t Matrix::getRows() const noexcept
  {
    return rows_;
  }

  size_t Matrix::getColumns() const noexcept
  {
    return columns_;
  }

  void Matrix::insert(shapePtr shape, size_t row, size_t column)
  {
    size_t tempRow;
    if (rows_ == row)
    {
      tempRow = rows_ + 1;
    }
    else
    {
      tempRow = rows_;
    }
    size_t tempColumn;
    if (columns_ == column)
    {
      tempColumn = columns_ + 1;
    }
    else
    {
      tempColumn = columns_;
    }
    if ((tempRow != rows_) || (tempColumn != columns_))
    {
      shapesArray temp(std::make_unique<shapePtr[]>(tempColumn * tempRow));
      for (size_t i = 0; i < tempRow; i++)
      {
        for (size_t j = 0; j < tempColumn; j++)
        {
          if ((i != rows_) && (j != columns_))
          {
            temp[(i * tempColumn) + j] = shapes_[(i * columns_) + j];
          }
          else
          {
            temp[(i * tempColumn) + j] = nullptr;
          }
        }
      }
      temp[(row * tempColumn) + column] = shape;
      shapes_ = std::move(temp);
      rows_ = tempRow;
      columns_ = tempColumn;
    }
    else
    {
      shapes_[(row * tempColumn) + column] = shape;
    }
  }

  void Matrix::insert(shapePtr shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Transmitting shape is nullptr");
    }
    size_t row = 0;
    size_t column = 0;
    for (size_t j = 0; j < getRows(); j++)
    {
      for (size_t k = 0; k < getColumns(); k++)
      {
        if (shapes_[(j * rows_) + k] == nullptr)
        {
          row = j;
          column = k;
          break;
        }
        if (intersection(shape->getFrameRect(), this->operator[](j)[k]->getFrameRect()))
        {
          row = j + 1;
          column = 0;
          break;
        }
        row = j;
        column = k + 1;
      }
      if (row != j + 1)
      {
        break;
      }
    }
    insert(shape, row, column);
  }

  Matrix::Layer::Layer(shapePtr* array, size_t size) :
    array_(array),
    size_(size)
  {}

  Matrix::shapePtr& Matrix::Layer::operator[](size_t index)
  {
    if (index > size_ - 1 || size_ == 0)
    {
      throw std::out_of_range("Index of column is invalid. Invalid index: "
        + std::to_string(index));
    }
    return array_[index];
  }
}
