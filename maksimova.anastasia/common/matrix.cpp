#include "matrix.hpp"
#include <stdexcept>

namespace maksimova
{
  Matrix::Matrix() :
    levels_(0),
    columns_(0),
    figure_(nullptr)
  {}

  Matrix::Matrix(const Matrix &element) :
    levels_(element.levels_),
    columns_(element.columns_),
    figure_(std::make_unique<shapePtr[]>(element.columns_ * element.levels_))
  {
    for (size_t i = 0; i < (levels_ * columns_); i++)
    {
      figure_[i] = element.figure_[i];
    }
  }

  Matrix::Matrix(Matrix &&element) :
  levels_(element.levels_),
  columns_(element.columns_),
  figure_(std::move(element.figure_))
  {
    element.levels_ = 0;
    element.columns_ = 0;
  }

  Matrix::Layer::Layer(maksimova::Matrix::shapePtr *shape, size_t size) :
    shape_(shape),
    size_(size)
  {}

  Matrix & Matrix::operator=(const Matrix &element)
  {
    if(&element == this)
    {
      return *this;
    }
    if(levels_ == element.levels_ && columns_ == element.columns_)
    {
      for(size_t i = 0; i < levels_ * columns_; ++i)
      {
        figure_[i] = element.figure_[i];
      }
    }
    else
    {
      matrixPtr temp(std::make_unique<shapePtr[]>(element.columns_ * element.levels_));
      for(size_t i = 0; i < element.levels_ * element.columns_; ++i)
      {
        temp[i] = element.figure_[i];
      }
      levels_ = element.levels_;
      columns_ = element.columns_;
      figure_ = std::move(temp);
    }
    return *this;
  }

  Matrix::shapePtr & Matrix::Layer::operator[](size_t index)
  {
    if(size_ == 0 || index > size_ - 1)
    {
      throw std::out_of_range("Invalid index received: " + std::to_string(index));
    }
    return shape_[index];
  }

  Matrix::Layer Matrix::operator[](const size_t index)
  {
    if(levels_ == 0 || index > levels_)
    {
      throw std::out_of_range("Invalid index received: " + std::to_string(index));
    }
    return Matrix::Layer(&figure_[columns_ * index], columns_);
  }

  void Matrix::addElement(const shapePtr &shape)
  {
    if (shape == nullptr)
    {
      throw std::invalid_argument("Shape is nullptr!");
    }
    if(levels_ == 0 && columns_ == 0)
    {
      levels_ = 1;
      columns_ = 1;
      figure_ = std::make_unique<shapePtr[]>(1);
      figure_[0] = shape;
      return;
    }
    int required_level = -1;
    for(size_t i = 0; i < levels_; ++i)
    {
      for(size_t j = 0; j < columns_; ++j)
      {
        if(check_above(shape, figure_[i * columns_ + j]))
        {
          required_level = i;
        }
      }
    }
    if(required_level < static_cast<int>(levels_) - 1)
    {
      if(!figure_[(required_level + 1) * columns_ + columns_ - 1])
      {
        for(size_t i = (required_level + 1) * columns_; i <= (required_level + 1) * columns_ + columns_ - 1; ++i)
        {
          if(!figure_[i])
          {
            figure_[i] = shape;
            return;
          }
        }
      }
      else
      {
        matrixPtr new_matrix = std::make_unique<shapePtr[]>(levels_ * (columns_ + 1));
        for(size_t i = 0; i < levels_; ++i)
        {
          for(size_t j = 0; j < columns_ ; ++j)
          {
            new_matrix[i * (columns_ + 1)+ j] = figure_[i * columns_ + j];
          }
        }
        figure_ = std::move(new_matrix);
        figure_[(required_level + 1) * (columns_ + 1)+ columns_] = shape;
        ++columns_;
        return;
      }
    }
    matrixPtr new_matrix = std::make_unique<shapePtr[]>((levels_ + 1) * columns_);
    for(size_t i = 0; i < levels_ * columns_; ++i)
    {
      new_matrix[i] = figure_[i];
    }
    figure_ = std::move(new_matrix);
    figure_[levels_ * columns_] = shape;
    ++levels_;
  }

  bool Matrix::check_above(const shapePtr &shape1, const shapePtr &shape2) const noexcept
  {
    if(!shape1 || !shape2)
      return false;
    rectangle_t rec1 = shape1->getFrameRect();
    rectangle_t rec2 = shape2->getFrameRect();
    return (abs(rec1.pos.x - rec2.pos.x) < (rec1.width / 2 +rec2.width / 2)
        && abs(rec1.pos.y - rec2.pos.y) < (rec1.height / 2 + rec2.width / 2));
  }

  size_t Matrix::getLevels() const noexcept
  {
    return levels_;
  }

  size_t Matrix::getColumns() const noexcept
  {
    return  columns_;
  }

  void Matrix::printInf() const
  {
    std::cout << "Information about matrix:\nColumns = " << getColumns()
        << "\t Levels = " << getLevels() << std::endl;
  }
}
