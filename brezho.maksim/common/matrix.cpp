#include "matrix.hpp"
#include <memory>
#include <stdexcept>
#include <string>
#include <cmath>
#include <iostream>
#include <numeric>

namespace brezho
{
  Matrix::Layer::Layer(shapePtr* layer, size_t size) :
    layer_(layer),
    size_(size)
  {}

  std::shared_ptr<Shape>& Matrix::Layer::operator[](size_t index)
  {
    if (index >= size_ || size_ == 0)
    {
      throw std::out_of_range(std::string("Layer index out of range,index = " + std::to_string(index)));
    }
    return layer_[index];
  }

  Matrix::Matrix() noexcept :
    matrix_(nullptr),
    layerUsedSize_(0),
    layerFullSize_(0),
    usedSize_(nullptr),
    fullSize_(0)
  {}

  Matrix::Matrix(const Matrix& otherMatrix) :
    matrix_(std::make_unique<std::shared_ptr<Shape>[]>(otherMatrix.layerFullSize_)),
    layerUsedSize_(otherMatrix.layerUsedSize_),
    layerFullSize_(otherMatrix.layerFullSize_),
    usedSize_(std::make_unique<size_t[]>(otherMatrix.layerUsedSize_)),
    fullSize_(otherMatrix.fullSize_)
  {
    for (size_t i = 0; i < otherMatrix.layerUsedSize_; i++)
    {
      usedSize_[i] = otherMatrix.usedSize_[i];
    }
    for (size_t i = 0; i < fullSize_ * layerUsedSize_; i++)
    {
      matrix_[i] = otherMatrix.matrix_[i];
    }
  }

  Matrix::Layer Matrix::operator[](size_t index)
  {
    if (index >= layerUsedSize_)
    {
      throw std::out_of_range(std::string("The index of Matrix is outside of acceptable values. Index = " + std::to_string(index)));
    }
    return Layer(&matrix_[fullSize_ * index], usedSize_[index]);
  }

  Matrix& Matrix::operator=(const Matrix& otherMatrix)
  {
    if (this == &otherMatrix)
    {
      return *this;
    }
    matrixPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(otherMatrix.layerFullSize_);
    std::unique_ptr<size_t[]> tempSize = std::make_unique<size_t[]>(otherMatrix.layerFullSize_);
    for (size_t i = 0; i < otherMatrix.layerUsedSize_ * fullSize_; i++)
    {
      temp[i] = otherMatrix.matrix_[i];
    }
    for (size_t i = 0; i < layerUsedSize_; i++)
    {
      tempSize[i] = otherMatrix.usedSize_[i];
    }
    fullSize_ = otherMatrix.fullSize_;
    matrix_ = std::move(temp);
    usedSize_ = std::move(tempSize);
    layerUsedSize_ = otherMatrix.layerUsedSize_;
    layerFullSize_ = otherMatrix.layerFullSize_;
    return *this;
  }

  void Matrix::addShape(const shapePtr& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape of Matrix is nullptr.");
    }
    if (layerUsedSize_ == 0)
    {
      addLayer();
      usedSize_[layerUsedSize_]++;
      matrix_[layerUsedSize_] = shape;
      layerUsedSize_++;
      return;
    }
    int lastSuperimposed = -1;
    size_t count = 0;
    for (size_t i = 0; i < layerUsedSize_; i++)
    {
      for (size_t j = 0; j < usedSize_[i]; ++j)
      {
        if (isSuperimposed(shape, matrix_[j + count]))
        {
          lastSuperimposed = i;
        }
      }
      count += fullSize_;
    }
    if (lastSuperimposed < static_cast<int>(layerUsedSize_ - 1))
    {
      if (usedSize_[lastSuperimposed + 1] == fullSize_)
      {
        increaseLayerSize();
      }
      size_t sum = fullSize_ * (lastSuperimposed + 1);
      matrix_[sum + usedSize_[lastSuperimposed + 1]] = shape;
      ++usedSize_[lastSuperimposed + 1];
    }
    else
    {
      if (layerFullSize_ == layerUsedSize_)
      {
        addLayer();
      }
      size_t sum = fullSize_ * layerUsedSize_;
      matrix_[sum] = shape;
      usedSize_[layerUsedSize_]++;
      layerUsedSize_++;
    }
  }

  size_t Matrix::getLayerSize() const noexcept
  {
    return layerUsedSize_;
  }

  size_t Matrix::getLayerCapacity() const noexcept
  {
    return layerFullSize_;
  }

  size_t Matrix::getShapeCount(size_t layerNumber) const
  {
    if (layerNumber >= layerUsedSize_)
    {
      throw std::out_of_range(std::string("Invalid value for layerNumber. Layer number = " + std::to_string(layerNumber)));
    }
    return usedSize_[layerNumber];
  }

  void Matrix::printMatrixAreas(std::ostream& out)
  {
    size_t count = 0;
    for (size_t i = 0; i < layerUsedSize_; i++)
    {
      for (size_t j = 0; j < usedSize_[i]; j++)
      {
        out << matrix_[j + count]->getArea() << ' ';
      }
      count += fullSize_;
      out << std::endl;
    }
  }

  void Matrix::increaseLayerSize()
  {
    const size_t coefficient = 2;
    matrixPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(fullSize_ * layerFullSize_ * coefficient);
    size_t tempCount = 0, matrixCount = 0;
    for (size_t i = 0; i < layerUsedSize_; i++)
    {
      for (size_t j = 0; j < fullSize_; ++j)
      {
        temp[tempCount] = matrix_[matrixCount];
        ++tempCount;
        ++matrixCount;
      }
      tempCount += fullSize_;
    }
    matrix_ = std::move(temp);
    fullSize_ *= coefficient;
  }

  void Matrix::addLayer()
  {
    if (layerFullSize_ == 0)
    {
      std::unique_ptr<size_t[]> tempSize = std::make_unique<size_t[]>(1);
      matrixPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(1);
      matrix_ = std::move(temp);
      usedSize_ = std::move(tempSize);
      fullSize_ = 1;
      layerFullSize_ = 1;
      return;
    }
    const int coefficient = 2;
    matrixPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(fullSize_ * layerFullSize_ * coefficient);
    std::unique_ptr<size_t[]> tempSize = std::make_unique<size_t[]>(layerFullSize_ * coefficient);
    for (size_t i = 0; i < layerUsedSize_; i++)
    {
      tempSize[i] = usedSize_[i];
    }
    for (size_t i = 0; i < layerUsedSize_ * fullSize_; i++)
    {
      temp[i] = matrix_[i];
    }
    layerFullSize_ *= coefficient;
    usedSize_ = std::move(tempSize);
    matrix_ = std::move(temp);
  }

  bool Matrix::isSuperimposed(const shapePtr& shape1, const shapePtr& shape2)
  {
    if (shape1 == nullptr || shape2 == nullptr)
    {
      return false;
    }
    return ((abs(shape1->getFrameRect().pos.x - shape2->getFrameRect().pos.x)
      < ((shape1->getFrameRect().width / 2) + (shape2->getFrameRect().width / 2)))
      && ((abs(shape1->getFrameRect().pos.y - shape2->getFrameRect().pos.y)
      < ((shape1->getFrameRect().height / 2) + (shape1->getFrameRect().height / 2)))));
  }

}
