#include "matrix.hpp"
#include <stdexcept>
#include <string>

namespace kichigin
{
  Matrix::Matrix(unsigned int layerFullSize):
    matrix_(nullptr),
    matrixFullSize_(0),
    layerFullSize_(layerFullSize)
  {}

  Matrix::Matrix(const Matrix& matrix):
    matrix_(new std::shared_ptr<Shape>[matrix.matrixFullSize_]),
    matrixFullSize_(matrix.matrixFullSize_),
    layerFullSize_(matrix.layerFullSize_)
  {
    for (unsigned int i = 0; i < matrixFullSize_; i++)
    {
      matrix_[i] = matrix.matrix_[i];
    }
  }

  Matrix& Matrix::operator=(const Matrix& matrix)
  {
    if (&matrix == this)
    {
      return *this;
    }
    matrix_.reset(new std::shared_ptr<Shape>[matrix.matrixFullSize_]);
    matrixFullSize_ = matrix.matrixFullSize_;
    layerFullSize_ = matrix.layerFullSize_;
    for (unsigned int i = 0; i < matrixFullSize_; i++)
    {
      matrix_[i] = matrix.matrix_[i];
    }
    return *this;
  }

  std::shared_ptr<Shape> Matrix::getShape(unsigned int row, unsigned int column) const
  {
    if (row >= getLayersNumber())
    {
      throw std::out_of_range(std::string("Matrix string index " + std::to_string(row) + " out of range"));
    }
    if (column >= getLayerCurrentSize(row))
    {
      throw std::out_of_range(std::string("Matrix column index " + std::to_string(column) + " out of range"));
    }
    return matrix_[row * layerFullSize_ + column];
  }


  void Matrix::addShape(const std::shared_ptr<Shape>& shape)
  {
    if (!layerFullSize_)
    {
      ++layerFullSize_;
    }
    unsigned int layerOfAdding = 0;
    unsigned int indexOfAdding = 0;
    for (unsigned int i = 0; i < getLayersNumber(); i++)
    {
      for (unsigned int j = 0; j < getLayerCurrentSize(i) && layerOfAdding <= i; j++)
      {
        if (layerOfAdding == i)
        {
          ++indexOfAdding;
        }
        if (isShapeOverclaped(matrix_[i * layerFullSize_ + j], shape) || j == layerFullSize_ - 1)
        {
          layerOfAdding = i + 1;
          indexOfAdding = 0;
        }
      }
    }
    if (layerOfAdding < getLayersNumber())
    {
      matrix_[layerOfAdding * layerFullSize_ + indexOfAdding] = shape;
    }
    else
    {
      arrayType temp(new std::shared_ptr<Shape>[matrixFullSize_ + layerFullSize_]);
      for (unsigned int i = 0; i < matrixFullSize_; i++)
      {
        temp[i] = matrix_[i];
      }
      matrix_ = std::move(temp);
      matrix_[matrixFullSize_] = shape;
      matrixFullSize_ += layerFullSize_;
    }
  }

  void Matrix::addCompositeShape(const std::shared_ptr<CompositeShape>& compShape)
  {
    for (unsigned int i = 0; i < compShape->getCurrentSize(); i++)
    {
      addShape((*compShape)[i]);
    }
  }

  unsigned int Matrix::getFullSize() const noexcept
  {
    return matrixFullSize_;
  }

  unsigned int Matrix::getLayersNumber() const noexcept
  {
    return matrixFullSize_ / layerFullSize_;
  }

  unsigned int Matrix::getLayerFullSize() const noexcept
  {
    return layerFullSize_;
  }

  unsigned int Matrix::getLayerCurrentSize(unsigned int index) const
  {
    if (index >= getLayersNumber())
    {
      throw std::out_of_range(std::string("Layer index " + std::to_string(index) + " is out of range"));
    }
    unsigned int count = 0;
    for (unsigned int i = index * layerFullSize_; i < (index + 1) * layerFullSize_; i++)
    {
      if (matrix_[i] == nullptr)
      {
        return count;
      }
      ++count;
    }
    return count;
  }

  bool Matrix::isShapeOverclaped(const std::shared_ptr<Shape>& first, const std::shared_ptr<Shape>& second)
  {
    if (first == nullptr || second == nullptr)
    {
      return false;
    }
    rectangle_t firstFrameRect = first->getFrameRect();
    rectangle_t secondFrameRect = second->getFrameRect();
    return ((abs(firstFrameRect.pos.x - secondFrameRect.pos.x)
          < ((firstFrameRect.width / 2) + (secondFrameRect.width / 2)))
        && ((abs(firstFrameRect.pos.y - secondFrameRect.pos.y)
          < ((firstFrameRect.height / 2) + (secondFrameRect.height / 2)))));
  }
}
