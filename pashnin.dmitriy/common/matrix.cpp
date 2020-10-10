
#include "matrix.hpp"
#include <stdexcept>

pashnin::Matrix::Matrix() :
  items_(std::make_unique<shapePtr[]>(0)),
  rows_(0),
  columns_(0)
{}

pashnin::Matrix::Matrix(const pashnin::Matrix &other) :
  items_(std::make_unique<shapePtr[]>(other.rows_ * other.columns_)),
  rows_(other.rows_),
  columns_(other.columns_)
{
  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    items_[i] = other.items_[i];
  }
}

pashnin::Matrix::Matrix(pashnin::Matrix &&other) noexcept:
  items_(std::move(other.items_)),
  rows_(other.rows_),
  columns_(other.columns_)
{
  other.items_.reset();
  other.rows_ = 0;
  other.columns_ = 0;
}

pashnin::Matrix &pashnin::Matrix::operator=(const pashnin::Matrix &other)
{
  if (this == &other)
  {
    return *this;
  }
  std::unique_ptr<shapePtr[]> tmpShapes(new shapePtr[rows_ * columns_]);
  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    tmpShapes[i] = other.items_[i];
  }
  items_ = std::move(tmpShapes);
  rows_ = other.rows_;
  columns_ = other.columns_;
  return *this;
}

std::shared_ptr<pashnin::Shape> &pashnin::Matrix::getShape(size_t row, size_t column)
{
  if (row >= rows_)
  {
    throw std::out_of_range("Matrix row index must be less than matrix rows quantity!");
  }
  if (column >= columns_)
  {
    throw std::out_of_range("Matrix column index must be less than matrix column quantity!");
  }
  
  return items_[row * columns_ + column];
}

void pashnin::Matrix::addShape(const shapePtr &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Shape must not be null!");
  }
  size_t rowToInsert = 1;
  
  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    if (items_[i])
    {
      if (isOverlapping(items_[i], shape))
      {
        rowToInsert = i / columns_ + 2;
      }
    }
  }
  
  size_t tmpRow = rows_;
  size_t tmpCol = columns_;
  size_t freeColumns = 0;
  if (rowToInsert <= rows_)
  {
    for (size_t i = (rowToInsert - 1) * columns_; i < rowToInsert * columns_; i++)
    {
      if (!items_[i])
      {
        freeColumns++;
      }
    }
  }
  else
  {
    tmpRow++;
    freeColumns = columns_;
  }
  if (!freeColumns)
  {
    tmpCol++;
    freeColumns++;
  }
  if (tmpCol > columns_ || tmpRow > rows_)
  {
    std::unique_ptr<shapePtr[]> tmpItems(std::make_unique<shapePtr[]>(tmpRow * tmpCol));
    
    for (size_t i = 0; i < tmpRow; i++)
    {
      for (size_t j = 0; j < tmpCol; j++)
      {
        if (i >= rows_ || j >= columns_)
        {
          tmpItems[i * tmpCol + j] = nullptr;
        }
        else
        {
          tmpItems[i * tmpCol + j] = items_[i * columns_ + j];
        }
      }
    }
    tmpItems[rowToInsert * tmpCol - freeColumns] = shape;
    
    rows_ = tmpRow;
    columns_ = tmpCol;
    items_ = std::move(tmpItems);
  }
  else
  {
    items_[rowToInsert * tmpCol - freeColumns] = shape;
  }
}

bool pashnin::Matrix::isOverlapping(const shapePtr &first, const shapePtr &second) const
{
  if (!first || !second)
  {
    throw std::invalid_argument("Shapes must not be null to check!");
  }
  const rectangle_t firstRect = first->getFrameRect();
  const rectangle_t secondRect = second->getFrameRect();
  return ((std::abs(firstRect.pos.x - secondRect.pos.x) < ((firstRect.width / 2) + (secondRect.width / 2)))
          && (std::abs(firstRect.pos.y - secondRect.pos.y) < ((firstRect.height / 2) + (secondRect.height / 2))));
  
}
