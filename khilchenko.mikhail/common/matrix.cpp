#include "matrix.hpp"

namespace khilchenko
{
  Matrix::Matrix():
    amountOfRows_(0),
    amountOfColumns_(0),
    matrix_(nullptr)
  {}

  Matrix::Matrix(const Matrix& other):
    amountOfRows_(other.amountOfRows_),
    amountOfColumns_(other.amountOfColumns_),
    matrix_(new std::shared_ptr<Shape>[other.amountOfRows_ * other.amountOfColumns_])
  {
    for(size_t i = 0; i < (amountOfColumns_*amountOfRows_); i++)
    {
      matrix_[i] = other.matrix_[i];
    }
  }

  Matrix::Matrix(Matrix&& other) noexcept:
    amountOfRows_(other.amountOfRows_),
    amountOfColumns_(other.amountOfColumns_),
    matrix_(std::move(other.matrix_))
  {
    other.amountOfRows_ = 0;
    other.amountOfColumns_ = 0;
    other.matrix_.reset();
  }

  Matrix& Matrix::operator=(const Matrix& other)
  {
    if (&other == this)
    {
      return *this;
    }
    if (amountOfColumns_ == other.amountOfColumns_ && amountOfRows_ == other.amountOfRows_)
    {
      for (size_t i = 0; i < (other.amountOfRows_ * amountOfColumns_); i++)
      {
        matrix_[i] = other.matrix_[i];
      }
    }
    else
    {
      arrayPtr temp(std::make_unique<std::shared_ptr<Shape>[]>(other.amountOfRows_
          * other.amountOfColumns_));
      for (size_t i = 0; i < (other.amountOfRows_ * amountOfColumns_); i++)
      {
        temp[i] = other.matrix_[i];
      }
      amountOfRows_ = other.amountOfRows_;
      amountOfColumns_ = other.amountOfColumns_;
      matrix_ = std::move(temp);
    }
    return *this;
  }

  Matrix& Matrix::operator=(Matrix&& other) noexcept
  {
    if (&other == this)
    {
      return *this;
    }
    amountOfRows_ = other.amountOfRows_;
    amountOfColumns_ = other.amountOfColumns_;
    matrix_ = std::move(other.matrix_);
    other.amountOfRows_ = 0;
    other.amountOfColumns_ = 0;
    other.matrix_.reset();
    return *this;
  }

  void Matrix::addShape(const std::shared_ptr<Shape>& shape)
  {
    if(shape == nullptr)
    {
      throw std::invalid_argument("Shape is nullptr");
    }
    if(amountOfColumns_ == 0 && amountOfRows_ == 0)
    {
      amountOfRows_ = 1;
      amountOfColumns_ = 1;
      matrix_ = std::make_unique<std::shared_ptr<Shape>[]>(1);
      matrix_[0] = shape;
    }
    else
    {
      int insertIndex = -1;
      int insertRow = -1;
      for(size_t i = 0; i < amountOfRows_; i++)
      {
        if(insertRow == -1)
        {
          insertRow = i;
        }
        for(size_t j = i * amountOfColumns_; j < (i + 1) * amountOfColumns_; j++)
        {
          if(isShapesOverlaped(shape, matrix_[j]) == true)
          {
            insertRow = -1;
            insertIndex = -1;
            break;
          }
          if(insertIndex == -1 && matrix_[j] == nullptr)
          {
            insertIndex = j;
          }
        }
      }
      if(insertIndex != -1)
      {
        matrix_[insertIndex] = shape;
      }
      else if(insertRow != -1)
      {
        arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>((amountOfColumns_
            + 1) * amountOfRows_);
        for(size_t j = 0; j < amountOfRows_; j++)
        {
          for(size_t k = j * amountOfColumns_;
              k < (j + 1) *amountOfColumns_;
              k++)
          {
            temp[k] = matrix_[k];
          }
        }    
        matrix_ = std::move(temp);
        temp = nullptr;
        matrix_[insertRow * (amountOfColumns_ + 1) + amountOfColumns_] = shape;
        amountOfColumns_++;
      }
      else
      {
        arrayPtr temp = std::make_unique<std::shared_ptr<Shape>[]>(amountOfColumns_ * (amountOfRows_ + 1));
        for(size_t i = 0; i < (amountOfColumns_ * amountOfRows_); i++)
        {
          temp[i] = matrix_[i];
        }
        matrix_ = std::move(temp);
        temp = nullptr;
        matrix_[amountOfRows_ * amountOfColumns_] = shape;
        amountOfRows_++;
      }
    }
  }

  std::shared_ptr<Shape>& Matrix::getShape(size_t row, size_t column)
  {
    if(row >= amountOfRows_ || column >= amountOfColumns_)
    {
      throw std::invalid_argument("Indices of row and column must be positive integer number,not superior than "
          + std::to_string(amountOfRows_) + " and " + std::to_string(amountOfColumns_)
          + " respectively. Invalid arguments: " + std::to_string(row) + " " + std::to_string(column));
    }
    return matrix_[row * amountOfColumns_ + column];
  }

  bool Matrix::isShapesOverlaped(const std::shared_ptr<Shape>& first, const std::shared_ptr<Shape>& second)
  {
    if(first == nullptr || second == nullptr)
    {
      return false;
    }
    double left1 = first->getCenter().x - (first->getFrameRect().width / 2);
    double up1 = first->getCenter().y + (first->getFrameRect().height / 2);
    double right1 = first->getCenter().x + (first->getFrameRect().width / 2);
    double down1 = first->getCenter().y - (first->getFrameRect().height / 2);
    double left2 = second->getCenter().x - (second->getFrameRect().width / 2);
    double up2 = second->getCenter().y + (second->getFrameRect().height / 2);
    double right2 = second->getCenter().x + (second->getFrameRect().width / 2);
    double down2 = second->getCenter().y - (second->getFrameRect().height / 2);
    return(!(left1 >= right2 || up1 <= down2 || up2 <= down1 || left2 >= right1));
  }

  size_t Matrix::getAmountOfRows()const noexcept
  {
    return amountOfRows_;
  }

  size_t Matrix::getAmountOfColoumns()const noexcept
  {
    return amountOfColumns_;
  }
}
