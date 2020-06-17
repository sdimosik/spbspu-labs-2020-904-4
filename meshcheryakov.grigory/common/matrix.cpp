#include "matrix.hpp"
#include <stdexcept>
#include <string>

namespace meshcheryakov
{
  Matrix::Layer::Layer(std::shared_ptr<Shape> *shapes,size_t size) :
    shapes_(shapes),
    size_(size)
  {}

  std::shared_ptr<Shape> &Matrix::Layer::operator[](size_t index)
  {
    if (index > size_ || size_ == 0)
    {
      throw std::out_of_range(std::string("Layer index is out of range. Wrong index = ") + std::to_string(index));
    }
    return shapes_[index];
  }

  Matrix::Matrix() :
    matrix_(nullptr),
    columns_(0),
    rows_(0)
  {}

  Matrix::Matrix(const Matrix &otherMatrix) :
    matrix_(std::make_unique<std::shared_ptr<Shape>[]>(otherMatrix.columns_ * otherMatrix.rows_)),
    columns_(otherMatrix.columns_),
    rows_(otherMatrix.rows_)
  {
    for (size_t i = 0; i < (columns_ * rows_); i++)
    {
      matrix_[i] = otherMatrix.matrix_[i];
    }
  }

  Matrix::Matrix(Matrix &&otherMatrix) noexcept :
    matrix_(std::move(otherMatrix.matrix_)),
    columns_(otherMatrix.columns_),
    rows_(otherMatrix.rows_)
  {
    otherMatrix.columns_ = 0;
    otherMatrix.rows_ = 0;
    otherMatrix.matrix_.reset();
  }

  Matrix& Matrix::operator=(const Matrix &otherMatrix)
  {
    if (this == &otherMatrix)
    {
      return *this;
    }
    if (columns_ == otherMatrix.columns_ && rows_ == otherMatrix.rows_)
    {
      for (size_t i = 0; i < (otherMatrix.columns_ * rows_); i++)
      {
        matrix_[i] = otherMatrix.matrix_[i];
      }
    }
    else
    {
      matrixPtr temp(std::make_unique<std::shared_ptr<Shape>[]>(otherMatrix.columns_ * otherMatrix.rows_));
      for (size_t i = 0; i < (otherMatrix.columns_ * columns_); i++)
      {
        temp[i] = otherMatrix.matrix_[i];
      }
      columns_ = otherMatrix.columns_;
      rows_ = otherMatrix.rows_;
      matrix_ = std::move(temp);
    }
    return *this;
  }

  Matrix& Matrix::operator=(Matrix &&otherMatrix) noexcept
    {
      if (&otherMatrix == this)
      {
        return *this;
      }
      else
      {
        columns_ = otherMatrix.columns_;
        rows_ = otherMatrix.rows_;
        matrix_ = std::move(otherMatrix.matrix_);
        otherMatrix.columns_ = 0;
        otherMatrix.rows_ = 0;
        otherMatrix.matrix_.reset();
        return *this;
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

  void Matrix::addShape(const std::shared_ptr<Shape> &shape)
  {
    if(shape == nullptr)
    {
      throw std::invalid_argument("Error: Shape is nullptr");
    }
    for (size_t i = 0; i < (columns_ * rows_); i++)
    {
      if (matrix_[i] == shape)
      {
        throw std::invalid_argument("Object already in the matrix!");
      }
    }
    size_t shapeRow = 1;
    for (size_t i = 0; i < rows_ * columns_; i++)
    {
      if (checkOverLapping(matrix_[i], shape))
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
        if (matrix_[i] == nullptr)
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
    if ((tempRow != rows_) || (tempColumn != columns_))
    {
      matrixPtr tempMatrix(std::make_unique<std::shared_ptr<Shape>[]>(tempColumn * tempRow));
      for (size_t i = 0; i < tempRow; i++)
      {
        for (size_t j = 0; j < tempColumn; j++)
        {
          if (i >= rows_ || j >= columns_)
          {
            tempMatrix[i * tempColumn + j] = nullptr;
            continue;
          }
          tempMatrix[i * tempColumn + j] = matrix_[i * columns_ + j];
        }
      }

      tempMatrix[shapeRow * tempColumn - freeColumns] = shape;

      matrix_ = std::move(tempMatrix);
      rows_ = tempRow;
      columns_ = tempColumn;
    }
    else
    {
      matrix_[shapeRow * tempColumn - freeColumns] = shape;
    }
  }

  Matrix::Layer Matrix::operator[](const size_t index)
  {
    if (rows_ == 0 || index > rows_)
    {
      throw std::out_of_range(std::string("Error. Index is out of range = ") += std::to_string(index));
    }
    return Layer(&matrix_[columns_ * index],columns_);
  }

  bool Matrix::checkOverLapping(const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2) const noexcept
  {
    if (shape1 == nullptr || shape2 == nullptr)
    {
      return false;
    }
    rectangle_t frame1 = shape1->getFrameRect();
    rectangle_t frame2 = shape2->getFrameRect();

    return ((std::abs(frame1.pos.x - frame2.pos.x)) < ((frame2.width / 2) + (frame2.width / 2)) && (std::abs(frame1.pos.y
        - frame2.pos.y) < ((frame1.height / 2) + (frame2.height / 2))));
  }

}
