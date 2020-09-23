#include "matrix.hpp"
#include <stdexcept>
#include <iostream>
#include <string>

namespace kundik
{
  Matrix::Matrix() :
    matrix_(nullptr),
    rows_(0),
    cols_(0)
  {}
  Matrix::Matrix(const Matrix& other) :
    matrix_(std::make_unique<std::shared_ptr<Shape>[]>(other.cols_* other.rows_)),
    rows_(other.rows_),
    cols_(other.cols_)
  {
    for (size_t i = 0; i < (cols_ * rows_); i++)
    {
      matrix_[i] = other.matrix_[i];
    }
  }
  Matrix::Matrix(Matrix&& other) noexcept :
    matrix_(std::move(other.matrix_)),
    rows_(other.rows_),
    cols_(other.cols_)
  {
    other.matrix_.reset();
    other.rows_ = 0;
    other.cols_ = 0;
  }
  Matrix& Matrix::operator=(const Matrix& other)
  {
    if (this == &other)
    {
      return *this;
    }
    std::unique_ptr<std::shared_ptr<Shape>[]> tmpShapes(new std::shared_ptr<Shape>[rows_ * cols_]);
    for (size_t i = 0; i < rows_ * cols_; i++)
    {
      tmpShapes[i] = other.matrix_[i];
    }
    matrix_ = std::move(tmpShapes);
    rows_ = other.rows_;
    cols_ = other.cols_;
    return *this;
  }
  Matrix& Matrix::operator=(Matrix&& other) noexcept
  {
    if (this == &other)
    {
      return *this;
    }
    matrix_ = std::move(other.matrix_);
    other.matrix_.reset();
    rows_ = other.rows_;
    other.rows_ = 0;
    cols_ = other.cols_;
    other.cols_ = 0;
    return *this;
  }
  void Matrix::addShape(const std::shared_ptr<Shape>& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape is empty");
    }
    size_t toInstert = 1;
    for (size_t i = 0; i < rows_ * cols_; i++)
    {
      if (isLapping(matrix_[i], shape))
      {
        toInstert = i / cols_ + 2;
      }
    }
    size_t tempRow = rows_;
    size_t tempCol = cols_;
    size_t freeCols = 0;
    if (toInstert > rows_)
    {
      tempRow++;
      freeCols = cols_;
    }
    else
    {
      for (size_t i = cols_ * (toInstert - 1); i < toInstert * cols_; i++)
      {
        if (matrix_[i] == nullptr)
        {
          freeCols++;
        }
      }
    }
    if (freeCols == 0)
    {
      tempCol++;
      freeCols = 1;
    }
    if (tempRow != rows_ || tempCol != cols_)
    {
      std::unique_ptr<std::shared_ptr<Shape>[]> tempElements(std::make_unique<std::shared_ptr<Shape>[]>(tempRow * tempCol));
      for (size_t i = 0; i < tempRow; i++)
      {
        for (size_t j = 0; j < tempCol; j++)
        {
          if (i >= rows_ || j >= cols_)
          {
            tempElements[i * tempCol + j] = nullptr;
            continue;
          }
          tempElements[i * tempCol + j] = matrix_[i * cols_ + j];
        }
      }
      tempElements[toInstert * tempCol - freeCols] = shape;
      matrix_ = std::move(tempElements);
      rows_ = tempRow;
      cols_ = tempCol;
    }
    else
    {
      matrix_[toInstert * tempCol - freeCols] = shape;
    }
  }
  std::shared_ptr<Shape>& Matrix::getShape(size_t row, size_t col)
  {
    if (row >= rows_)
    {
      throw std::out_of_range("Matrix row index more matrix rows count!");
    }
    if (col >= cols_)
    {
      throw std::out_of_range("Matrix column index more matrix column count!");
    }
    return matrix_[row * cols_ + col];
  }
  bool Matrix::isLapping(const std::shared_ptr<Shape>& shape1, const std::shared_ptr<Shape>& shape2) const noexcept
  {
    if (shape1 == nullptr || shape2 == nullptr)
    {
      return false;
    }
    return ((std::abs(shape1->getFrameRect().pos.x - shape2->getFrameRect().pos.x)) < ((shape2->getFrameRect().height / 2) + (shape2->getFrameRect().height / 2)) && (std::abs(shape1->getFrameRect().pos.y- shape2->getFrameRect().pos.y) < ((shape1->getFrameRect().width / 2) + (shape2->getFrameRect().width / 2))));
  }
}
