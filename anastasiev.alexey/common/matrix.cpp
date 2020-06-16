#include "matrix.hpp"

namespace anastasiev
{
  Matrix::Matrix() :
    rows_(0),
    columns_(0),
    elements_(nullptr)
  {}

  Matrix::Matrix(const Matrix &other) :
    rows_(other.rows_),
    columns_(other.columns_),
    elements_(std::make_unique<std::shared_ptr<Shape>[]>(other.rows_ * other.columns_))
  {
    for (unsigned int i = 0; i < rows_ * columns_; i++)
    {
      elements_[i] = other.elements_[i];
    }
  }

  Matrix &Matrix::operator=(const Matrix &other)
  {
    if (this == &other)
    {
      return *this;
    }
    std::unique_ptr<std::shared_ptr<Shape>[]> tempElemets(
        std::make_unique<std::shared_ptr<Shape>[]>(other.rows_ * other.columns_));
    rows_ = other.rows_;
    columns_ = other.columns_;
    for (unsigned int i = 0; i < rows_ * columns_; i++)
    {
      tempElemets[i] = other.elements_[i];
    }
    elements_.reset(nullptr);
    elements_.swap(tempElemets);
    return *this;
  }

  void Matrix::addShape(const std::shared_ptr<Shape> &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("No shape was given!");
    }
    if (rows_ == 0 && columns_ == 0)
    {
      elements_ = std::make_unique<std::shared_ptr<Shape>[]>(1);
      elements_[0] = shape;
      rows_ = 1;
      columns_ = 1;
    }
    else
    {
      int index = -1;
      int rowToAdd = -1;
      for (unsigned int i = 0; i < rows_; i++)
      {
        if (rowToAdd == -1)
        {
          rowToAdd = i;
        }
        for (unsigned int j = i * columns_; j < (i + 1) * columns_; j++)
        {
          if (isOverlapping(shape, elements_[j]))
          {
            rowToAdd = -1;
            index = -1;
            break;
          }
          if (elements_[j] == nullptr && rowToAdd == static_cast<int>(i))
          {
            index = j;
          }
        }
      }
      if (rowToAdd != -1)
      {
        if (index != -1)
        {
          elements_[index] = shape;
          return;
        }
        else
        {
          std::unique_ptr<std::shared_ptr<Shape>[]> temp =
              std::make_unique<std::shared_ptr<Shape>[]>(rows_ * (columns_ + 1));
          for (unsigned int j = 0; j < rows_; j++)
          {
            for (unsigned int k = j * columns_; k < (j + 1) * columns_; k++)
            {
              temp[k] = elements_[k];
            }
          }
          elements_.reset(nullptr);
          elements_.swap(temp);
          elements_[rowToAdd * (columns_ + 1) + columns_] = shape;
          columns_++;
          return;
        }
      }
      std::unique_ptr<std::shared_ptr<Shape>[]> temp =
          std::make_unique<std::shared_ptr<Shape>[]>(rows_ * (columns_ + 1));
      for (unsigned int i = 0; i < (rows_ * columns_); i++)
      {
        temp[i] = elements_[i];
      }
      elements_.reset(nullptr);
      elements_.swap(temp);
      elements_[rows_ * columns_] = shape;
      rows_++;
    }
  }

  std::shared_ptr<Shape> &Matrix::getShape(unsigned int row, unsigned int column)
  {
    if (row >= rows_ || column >= columns_)
    {
      throw std::out_of_range("Indexes of row or column is out of range.");
    }
    return elements_[row * columns_ + column];
  }

  bool Matrix::isOverlapping(const std::shared_ptr<Shape> &shape1, const std::shared_ptr<Shape> &shape2) const
  {
    if (shape1 == nullptr || shape2 == nullptr)
    {
      return false;
    }
    rectangle_t frame1 = shape1->getFrameRect();
    rectangle_t frame2 = shape2->getFrameRect();
    return (std::abs(frame1.pos.x - frame2.pos.x) <= (frame1.width / 2 + frame2.width / 2))
        && (std::abs(frame1.pos.y - frame2.pos.y) <= (frame1.height / 2 + frame2.height / 2));
  }
} // namespace anastasiev
