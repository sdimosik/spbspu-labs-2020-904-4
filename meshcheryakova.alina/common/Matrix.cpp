#include "Matrix.hpp"
#include <math.h>
namespace  meshcheryakova
{
  Matrix::Matrix() :
    rows_(0),
    columns_(0),
    list_of_shapes_(nullptr)
  { }

 Matrix::Matrix(const Matrix &other_matrix) :
   rows_(other_matrix.rows_),
   columns_(other_matrix.columns_),
   list_of_shapes_(std::make_unique<shape_ptr[]>(other_matrix.rows_ * other_matrix.columns_))
  {
    for (size_t i = 0; i < (rows_ * columns_); i++)
    {
      list_of_shapes_[i] = other_matrix.list_of_shapes_[i];
    }
  }

  Matrix::Matrix(Matrix &&other_matrix) noexcept :
    rows_(other_matrix.rows_),
    columns_(other_matrix.columns_),
    list_of_shapes_(std::move(other_matrix.list_of_shapes_))
  {
    other_matrix.rows_ = 0;
    other_matrix.columns_ = 0;
    other_matrix.list_of_shapes_.reset();

  }

  Matrix &Matrix::operator=(const Matrix &other_matrix)
  {
    if (this != &other_matrix)
    {
      shape_array temp_list(std::make_unique<shape_ptr[]>(other_matrix.rows_ * other_matrix.columns_));
      for (size_t i = 0; i < (other_matrix.rows_ * other_matrix.columns_); i++)
      {
        temp_list[i] = other_matrix.list_of_shapes_[i];
      }
      rows_ = other_matrix.rows_;
      columns_ = other_matrix.columns_;
      list_of_shapes_ = std::move(temp_list);
    }

    return *this;
  }

  Matrix &Matrix::operator =(Matrix &&other_matrix) noexcept
  {
    if (this != &other_matrix)
    {
      rows_ = other_matrix.rows_;
      columns_ = other_matrix.columns_;
      list_of_shapes_ = std::move(other_matrix.list_of_shapes_);
    }
    return *this;
  }

  Matrix:: shape_ptr &Matrix::getShape(size_t row, size_t column)
  {
    if (row >= rows_)
    {
      throw std::out_of_range("Matrix row index is out of range!");
    }
    if (column >= columns_)
    {
      throw std::out_of_range("Matrix column index is out of range!");
    }

    return list_of_shapes_[row * columns_ + column];
  }

  void Matrix::add(std::shared_ptr<Shape> &shape, size_t row, size_t column)
  {
    if(column < columns_ && row < rows_)
    {
      list_of_shapes_[row * columns_ + column] = shape;
    }
    else {
      size_t temp_rows = (row == rows_) ? (rows_ + 1) : (rows_);
      size_t temp_columns = (column == columns_) ? (columns_ + 1) : (columns_);

      shape_array temp_list(std::make_unique<shape_ptr[]>(temp_rows * temp_columns));

      for (size_t i = 0; i < temp_rows; i++) {
        for (size_t j = 0; j < temp_columns; j++) {
          if ((i == rows_) || (j == columns_)) {
            temp_list[i * temp_columns + j] = nullptr;
          } else {
            temp_list[i * temp_columns + j] = list_of_shapes_[i * columns_ + j];
          }
        }
      }
      temp_list[row * temp_columns + column] = shape;
      list_of_shapes_.swap(temp_list);
      rows_ = temp_rows;
      columns_ = temp_columns;
    }
  }

  bool Matrix::isOverlay(const std::shared_ptr<Shape> &first_shape, const std::shared_ptr<Shape> &second_shape) const
  {
    if (!first_shape || !second_shape)
    {
      throw std::invalid_argument("Shape must exist!");
    }
    const rectangle_t frame_rec1 = first_shape->getFrameRect();
    const rectangle_t frame_rec2 = second_shape->getFrameRect();
    double delta_spot_x = fabs(frame_rec1.pos.x - frame_rec2.pos.x);
    double delta_spot_y = fabs(frame_rec2.pos.y - frame_rec2.pos.y);
    double limit_of_x = (frame_rec1.width + frame_rec2.width) / 2;
    double limit_of_y = (frame_rec1.height + frame_rec2.height) / 2;
    return ((delta_spot_x < limit_of_x) && (delta_spot_y < limit_of_y));
  }

  void Matrix::separate(const shape_array &array, const size_t size)
  {
    for (size_t i = 0; i < size; i++)
    {
      size_t last_row = 0;
      size_t last_column = 0;
      for (size_t j = 0; j < this->getRows(); j++)
      {
        for (size_t k = 0; k < this->getColumns(); k++)
        {
          if (this->getShape(j,k) == nullptr)
          {
            last_row = j;
            last_column = k;
            break;
          }
          if (isOverlay(array[i], this->getShape(j,k)))
          {
            last_row = j + 1;
            last_column = 0;
            break;
          }
          else
            {
            last_row = j;
            last_column = k + 1;
          }
        }
        if (last_row == j)
        {
          break;
        }
      }
      this->add(array[i], last_row, last_column);
    }
  }

  void Matrix::separate(CompositeShape &comp_shape)
  {
    separate(comp_shape.getShapes(), comp_shape.getSize());
  }

  size_t Matrix::getRows() const noexcept
  {
    return rows_;
  }

  size_t Matrix::getColumns() const noexcept
  {
    return columns_;
  }
}



