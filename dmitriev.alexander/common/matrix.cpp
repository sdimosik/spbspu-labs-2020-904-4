#include "matrix.hpp"

dmitriev::Matrix::Matrix() :
  items_(std::make_unique<std::shared_ptr<Shape>[]>(0)),
  rows_(0),
  columns_(0)
{}

dmitriev::Matrix::Matrix(const dmitriev::Matrix &other) :
  items_(std::make_unique<std::shared_ptr<Shape>[]>(other.rows_ * other.columns_)),
  rows_(other.rows_),
  columns_(other.columns_)
{
  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    items_[i] = other.items_[i];
  }
}

dmitriev::Matrix::Matrix(dmitriev::Matrix &&other) noexcept :
  items_(std::move(other.items_)),
  rows_(other.rows_),
  columns_(other.columns_)
{
  other.items_.reset();
  other.rows_ = 0;
  other.columns_ = 0;
}

dmitriev::Matrix &dmitriev::Matrix::operator=(const dmitriev::Matrix &other)
{
  if (this == &other)
  {
    return *this;
  }
  std::unique_ptr<std::shared_ptr<Shape>[]> tmpShapes(new std::shared_ptr<Shape>[rows_ * columns_]);
  for (size_t i = 0; i < rows_ * columns_; i++)
  {
    tmpShapes[i] = other.items_[i];
  }
  items_ = std::move(tmpShapes);
  rows_ = other.rows_;
  columns_ = other.columns_;
  return *this;
}

std::shared_ptr<dmitriev::Shape> &dmitriev::Matrix::getShape(size_t row, size_t column)
{
  if (row >= rows_)
  {
    throw std::out_of_range("Matrix row index must be less than matrix rows count!");
  }
  if (column >= columns_)
  {
    throw std::out_of_range("Matrix column index must be less than matrix column count!");
  }

  return items_[row * columns_ + column];
}

void dmitriev::Matrix::addShape(const std::shared_ptr<Shape> &shape)
{
  if (!shape)
  {
    throw std::invalid_argument("Shape must not be null!");
  }
  size_t rowToInsert = 1;

  //Finding right position
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
  } else
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
    //Temp array
    std::unique_ptr<std::shared_ptr<Shape>[]> tmpItems(
      std::make_unique<std::shared_ptr<Shape>[]>(tmpRow * tmpCol));

    //Move data to temp array
    for (size_t i = 0; i < tmpRow; i++)
    {
      for (size_t j = 0; j < tmpCol; j++)
      {
        if (i >= rows_ || j >= columns_)
        {
          tmpItems[i * tmpCol + j] = nullptr;
        } else
        {
          tmpItems[i * tmpCol + j] = items_[i * columns_ + j];
        }
      }
    }
    //Add new
    tmpItems[rowToInsert * tmpCol - freeColumns] = shape;
    
    //Move data back
    rows_ = tmpRow;
    columns_ = tmpCol;
    items_ = std::move(tmpItems);
  } else
  {
    //Add new
    items_[rowToInsert * tmpCol - freeColumns] = shape;
  }
}

bool dmitriev::Matrix::isOverlapping(const std::shared_ptr<Shape> &first, const std::shared_ptr<Shape> &second) const
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
