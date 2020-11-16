#include "matrix.hpp"
#include <iostream>
#include <string>
#include <cmath>

namespace stolyarov
{
  Matrix::Layer::Layer(shapePtr* element, size_t size) :
    element_(element),
    size_(size)
  {}

  Matrix::shapePtr& Matrix::Layer::operator[](size_t index)
  {
    if (index > size_ - 1 || size_ == 0)
    {
      throw std::out_of_range("Invalid colomn index received. False index: " + std::to_string(index));
    }
    return element_[index];
  }

  Matrix::Matrix() :
    figure_(nullptr),
    levels_(0),
    columns_(0)
  {}

  Matrix::Matrix(const Matrix& element) :
    figure_(std::make_unique<shapePtr[]>(element.levels_* element.columns_)),
    levels_(element.levels_),
    columns_(element.columns_)
  {
    for (size_t i = 0; i < (levels_ * columns_); i++)
    {
      figure_[i] = element.figure_[i];
    }
  }

  Matrix& Matrix::operator=(const Matrix& element)
  {
    if (this == &element)
    {
      return *this;
    }
    else
    {
      matrixFigure temp = std::make_unique<shapePtr[]>(element.levels_ * element.columns_);
      for (size_t i = 0; i < element.levels_ * element.columns_; i++)
      {
        temp[i] = element.figure_[i];
      }
      levels_ = element.levels_;
      columns_ = element.columns_;
      figure_.swap(temp);
      return *this;
    }
  }
  Matrix::Layer Matrix::operator[](const size_t index)
  {
    if ((levels_ == 0) || (index > levels_))
    {
      throw std::out_of_range("Invalid layer index received. False index: " + std::to_string(index));
    }
    return Layer(&figure_[columns_ * index], columns_);
  }

  void Matrix::addElement(const Matrix::shapePtr& shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Error: the element of matrix received is null");
    }

    if (levels_ == 0)
    {
      columns_++;
      levels_++;
      figure_ = std::move(std::make_unique<shapePtr[]>(1));
      figure_[0] = shape;
      return;
    }

    int lastLevel = -1;
    for (size_t i = 0; i < levels_; ++i)
    {
      for (size_t j = 0; j < columns_; ++j)
      {
        if (checkIntersection(figure_[i * columns_ + j], shape))
        {
          lastLevel = i;
        }
      }
    }

    if (lastLevel < static_cast<int>(levels_ - 1))
    {
      if (figure_[(lastLevel + 1) * columns_ + (columns_ - 1)] == nullptr)
      {
        for (size_t i = (lastLevel + 1) * columns_; i <= (lastLevel + 1) * columns_ + (columns_ - 1); ++i)
        {
          if (figure_[i] == nullptr)
          {
            figure_[i] = shape;
            return;
          }
        }
      }
      else
      {
        matrixFigure newElements = std::make_unique<shapePtr[]>((levels_ * (columns_ + 1)));
        size_t temp = 0, tempFigure = 0;
        for (size_t i = 0; i < levels_; ++i)
        {
          for (size_t j = 0; j < columns_; ++j)
          {
            newElements[temp] = figure_[tempFigure];
            ++temp;
            ++tempFigure;
          }
          ++temp;
        }
        figure_ = std::move(newElements);
        ++columns_;
        figure_[(lastLevel + 1) * columns_ + (columns_ - 1)] = shape;
        return;
      }
    }
    matrixFigure newElements = std::make_unique<shapePtr[]>((levels_ + 1) * columns_);
    for (size_t i = 0; i < levels_ * columns_; ++i)
    {
      newElements[i] = figure_[i];
    }
    figure_ = std::move(newElements);
    ++levels_;
    figure_[(levels_ - 1) * columns_] = shape;
  }

  size_t Matrix::getLevels() const noexcept
  {
    return levels_;
  }

  size_t Matrix::getColumns() const noexcept
  {
    return columns_;
  }

  void Matrix::printInf() const
  {
    std::cout << "Matrix size = " << levels_ * columns_ << '\n' << "levels: " << getLevels()
        << " columns: " << getColumns() << '\n' << '\n';
  }

  bool Matrix::checkIntersection(const Matrix::shapePtr& shape1, const Matrix::shapePtr& shape2) const noexcept
  {
    if (shape1 == nullptr || shape2 == nullptr)
    {
      return false;
    }
    rectangle_t frame1 = shape1->getFrameRect();
    rectangle_t frame2 = shape2->getFrameRect();

    return (abs(frame1.pos.x - frame2.pos.x) < (frame1.width / 2 + frame2.width / 2)
        && abs(frame1.pos.y - frame2.pos.y) < (frame1.height / 2 + frame2.height / 2));
  }

}
